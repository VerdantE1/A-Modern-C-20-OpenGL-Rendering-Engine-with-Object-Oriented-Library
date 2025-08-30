#shader vertex 
#version 430
layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 normal;

out vec3 varyingNormal;
out vec3 varyingLightDir;
out vec3 varyingHalfVec;
out vec3 varyingVertPos;
out vec4 shadow_coord; // 阴影坐标/光源坐标

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
uniform mat4 lightSpaceMatrix; // 光源空间矩阵（投影矩阵 * 视图矩阵）

void main(void)
{
	// 计算视图空间位置
    vec4 P = mv_matrix * vec4(vertPos, 1.0);
    varyingVertPos = P.xyz;

	// 计算法向量
    varyingNormal = (norm_matrix * vec4(normal, 1.0)).xyz;

	// 计算光照方向
    varyingLightDir = light.position - varyingVertPos;


	//计算半向量（用于镜面反射）
    vec3 viewDir = normalize(-varyingVertPos);  // 视图方向
    vec3 lightDir = normalize(varyingLightDir);
    varyingHalfVec = normalize(lightDir + viewDir);

	//计算阴影坐标（使用世界坐标）
	shadow_coord = lightSpaceMatrix * vec4(vertPos,1.0);

	//输出到屏幕
	gl_Position = proj_matrix * P;
}

#shader fragment 
#version 430

// 从顶点着色器接收插值数据
in vec3 varyingNormal;
in vec3 varyingLightDir;
in vec3 varyingHalfVec;
in vec3 varyingVertPos;
in vec4 shadow_coord;

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
uniform sampler2D shadowMap; // 阴影贴图
uniform float shadowBias; // 阴影偏移


// 阴影计算函数
float ShadowCalculation(vec4 fragPosLightSpace)
{
	// 执行透视除法, 将齐次坐标转换为标准化设备坐标(NDC)
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

	// 转换到[0,1]范围
	projCoords = projCoords * 0.5 + 0.5; 

	// 边界检查
	if (projCoords.z > 1.0) return 0.0;

	// 获取当前片段的深度值
	float currentDepth = projCoords.z;

	// 从阴影贴图中获取深度值
	float closestDepth = texture(shadowMap, projCoords.xy).r;

	// 检查当前片段是否在阴影中
	float shadow = currentDepth - shadowBias > closestDepth ? 1.0:0.0;

	return shadow;


}

void main(void)
{
    vec3 N = normalize(varyingNormal);
    vec3 L = normalize(varyingLightDir);
    vec3 H = normalize(varyingHalfVec);

	// 计算阴影
	float shadow = ShadowCalculation(shadow_coord);
	float noInShadow = 1.0 - shadow; // 不在阴影中为1.0，在阴影中为0.0

	// 环境光
	fragColor = globalAmbient * material.ambient + light.ambient * material.ambient;

	// 只有不在阴影中才加入漫反射和镜面反射
	if(noInShadow == 1.0)
	{
		// 漫反射
        fragColor += light.diffuse * material.diffuse * max(dot(N, L), 0.0) * noInShadow;
        
        // 镜面反射
        fragColor += light.specular * material.specular * 
                    pow(max(dot(N, H), 0.0), material.shininess) * noInShadow;
	}
}