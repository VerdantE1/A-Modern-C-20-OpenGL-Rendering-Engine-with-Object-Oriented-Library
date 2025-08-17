#shader vertex 
#version 430
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 mvp_matrix;

out vec4 varyingColor;
out vec2 tc;

void main(void)
{
    gl_Position = mvp_matrix * vec4(position.x, position.y, position.z, 1.0);
    varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 1.0);
    tc = texCoord;
}

#shader fragment 
#version 430

in vec4 varyingColor;
in vec2 tc;

out vec4 color;

layout(binding = 0) uniform sampler2D sunSampler;
layout(binding = 1) uniform sampler2D earthSampler;
layout(binding = 2) uniform sampler2D moonSampler;
layout(binding = 3) uniform sampler2D sunRingSampler;  // 添加太阳环纹理采样器

uniform int objectType; 

void main(void)
{
    if(objectType == 0) {
        // 太阳
        color = texture(sunSampler, tc);
        
    } else if(objectType == 1) {
        // 地球
        color = texture(earthSampler, tc);
        
    } else if(objectType == 2) {
        // 月球
        color = texture(moonSampler, tc);
        
    } else if(objectType == 3) {
        // 太阳环 - 添加半透明效果和特殊处理
        vec4 ringColor = texture(sunRingSampler, tc);
        
        // 为环创建渐变透明效果 - 外边缘更透明
        float distanceFromCenter = distance(tc, vec2(0.5, 0.5)) * 2.0;
        float alpha = 1.0 - smoothstep(0.3, 1.0, distanceFromCenter);
        
        // 为环添加发光效果
        ringColor.rgb *= 1.5;  // 增强亮度
        ringColor.a = alpha * 0.6;  // 设置透明度
        
        color = ringColor;
        
    } else {
        color = vec4(1, 0, 1, 1);  // 错误颜色
    }
}