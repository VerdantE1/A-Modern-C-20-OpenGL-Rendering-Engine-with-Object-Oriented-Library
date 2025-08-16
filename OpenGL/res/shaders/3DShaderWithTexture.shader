#shader vertex
#version 430
layout(location = 0) in vec3 position; //从位于Buffer里的顶点属性槽0读取数据。
layout(location = 1) in vec2 texCoord;


uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec4 varyingColor;
out vec2 tc;

void main(void)
{
	gl_Position = proj_matrix * mv_matrix * vec4(position.x, position.y, position.z, 1.0);
	varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 1.0); // 将位置映射到颜色
	tc = texCoord; // 将纹理坐标传递给片段着色器
}



#shader fragment
#version 430

layout(binding =0) uniform sampler2D textureSampler; //绑定纹理单元0
in vec2 tc;											//从顶点着色器接收纹理坐标	
in vec4 varyingColor;								//从顶点着色器接收颜色数据
out vec4 color;										//把color输出到帧缓冲的第0个颜色附件（通常就是屏幕）
void main(void)
{
	color = texture(textureSampler,tc) ; //从纹理中采样颜色，并与顶点颜色混合
}