#shader vertex 
#version 430
layout (location = 0) in vec3 position; //从位于Buffer里的顶点属性槽0读取数据。
layout (location = 1) in vec2 texCoord;



uniform mat4 mvp_matrix; //模型视图投影矩阵

out vec4 varyingColor;
out vec2 tc;
void main(void)
{
	gl_Position =  mvp_matrix * vec4(position.x,position.y,position.z ,1.0);
	varyingColor = vec4(position,1.0) * 0.5 + vec4(0.5,0.5,0.5,1.0); // 将位置映射到颜色
	tc = texCoord;  // 关键的一行
}



#shader fragment 
#version 430

in vec4 varyingColor; //从顶点着色器接收颜色数据
in vec2 tc;

out vec4 color; //把color输出到帧缓冲的第0个颜色附件（通常就是屏幕）


layout(binding = 0) uniform sampler2D sunSampler;
layout(binding = 1) uniform sampler2D earthSampler;
layout(binding = 2) uniform sampler2D moonSampler;

uniform int objectType; 

void main(void)
{
    if(objectType == 0)
        color = texture(sunSampler, tc);
    else if(objectType == 1)
        color = texture(earthSampler, tc);
    else if(objectType == 2)
        color = texture(moonSampler, tc);
    else
        color = vec4(1,0,1,1);
}