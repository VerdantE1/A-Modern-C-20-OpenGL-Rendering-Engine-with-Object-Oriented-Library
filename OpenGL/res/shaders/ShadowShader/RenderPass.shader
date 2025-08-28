#shader vertex 
#version 430
layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 normal;

out vec3 varyingNormal,varyingLightDir,varyingHalfVec,varyingVertPos; 
out vec4 shadow_coord;

struct PositionalLight
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};

struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform mat4 mv_matrix; 
uniform mat4 proj_matrix;
uniform mat4 norm_matrix;
uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform Material material;
uniform shadowMVP2;
layout(binding = 0) uniform sampler2DShadow shTex;

void main(void)
{
	varyingVertPos = (mv_matrix * vec4(vertPos,1.0)).xyz;
	varyingNormal = (norm_matrix * vec4(normal,1.0)).xyz;
	varyingLightDir = light.position - varyingVertPos;
	varyingHalfVec = (varingLightDir - varyingVertPos).xyz;
	shadow_coord = shadowMVP2 * vec4(vertPos,1.0);
	gl_Position = proj_matrix * P;
}

#shader fragment 
#version 430

// 从顶点着色器接收插值数据
in vec3 varyingNormal;
in vec3 varyingLightDir;
in vec3 varyingViewDir;
in vec3 varyingVertPos;

out vec4 fragColor;

struct PositionalLight
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};

struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform vec4 globalAmbient; 
uniform PositionalLight light; 
uniform Material material; 
uniform mat4 mv_matrix; 
uniform mat4 proj_matrix; 
uniform mat4 norm_matrix; 

void main(void)
{
	vec3 N = normalize(varyingNormal);
	vec3 L = normalize(varyingLightDir);
	vec3 V = normalize(varyingViewDir);
	vec3 H = normalize(L + V);

	float notlnShadow = texture(shTex,shadow_coord.xyz);
	

	fragColor = globalAmbient * material.ambient + light.ambient * material.ambient;
	if(notlnShadow == 1.0)
	{
		fragColor += light.diffuse * material.diffuse * max(dot(N,L),0.0)
		+ light.specular * material.specular * pow(max(dot(N,H),0.0),material.shininess*3.0);
	}
			
}