#shader vertex 
#version 430
layout (location = 0) in vec3 position; //从位于Buffer里的顶点属性槽0读取数据。
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 normal;
out vec4 varyingColor;


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

	//将顶点位置转换到视觉空间
	//将法向量转换到视觉空间
	//计算视觉空间光照向量(从顶点到光源)
	vec4 P = mv_matrix * vec4(position,1.0);
	vec3 N = normalize((norm_matrix * vec4(normal,1.0)).xyz);  
	vec3 L = normalize(light.position - P.xyz); 
	vec3 V = normalize(-P.xyz);
	vec3 R = reflect(-L,N);

	//环境光、漫反射和镜面反射分量
	vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz;
	vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(dot(N,L),0.0);
	vec3 specular = material.specular.xyz * light.specular.xyz * pow(max(dot(R,V),0.0f),material.shininess);

	//将各个分量相加得到最终颜色
	varyingColor = vec4(ambient + diffuse + specular,1.0);
	gl_Position = proj_matrix * mv_matrix * vec4(position ,1.0);

}



#shader fragment 
#version 430

in vec4 varyingColor; //从顶点着色器接收颜色数据
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
	fragColor = varyingColor;
}