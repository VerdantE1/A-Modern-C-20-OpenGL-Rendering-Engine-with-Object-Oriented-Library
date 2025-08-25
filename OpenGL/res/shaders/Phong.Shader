#shader vertex 
#version 430
layout (location = 0) in vec3 position; //从位于Buffer里的顶点属性槽0读取数据。
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 normal;


// Phong着色需要将这些数据传递给片段着色器
out vec3 varyingNormal; 
out vec3 varyingLightDir;
out vec3 varyingViewDir;
out vec3 varyingVertPos;

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

void main(void)
{


	vec4 P = mv_matrix * vec4(position,1.0);

	varyingVertPos = P.xyz;
	varyingNormal = (norm_matrix * vec4(normal,1.0)).xyz;
	varyingLightDir = light.position - P.xyz;
	varyingViewDir = -P.xyz;

	gl_Position = proj_matrix * mv_matrix * vec4(position ,1.0);

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
		// 归一化插值后的向量
	vec3 N = normalize(varyingNormal);
	vec3 L = normalize(varyingLightDir);
	vec3 V = normalize(varyingViewDir);
	vec3 R = reflect(-L, N);
	

	//环境光、漫反射和镜面反射分量
	vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz;
	vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(dot(N,L),0.0);
	vec3 specular = material.specular.xyz * light.specular.xyz * pow(max(dot(R,V),0.0f),material.shininess);

	fragColor = vec4(ambient + diffuse + specular, 1.0);
}