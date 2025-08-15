#shader vertex 
#version 430
layout (location = 0) in vec3 position; //从位于Buffer里的顶点属性槽0读取数据。
layout (location = 1) in vec3 color;


//uniform mat4 mv_matrix; 
//uniform mat4 proj_matrix;
uniform mat4 mvp_matrix; //模型视图投影矩阵
out vec4 varyingColor;
void main(void)
{
	gl_Position =  mvp_matrix * vec4(position.x,position.y,position.z ,1.0);
	varyingColor = vec4(position,1.0) * 0.5 + vec4(0.5,0.5,0.5,1.0); // 将位置映射到颜色
}



#shader fragment 
#version 430

in vec4 varyingColor; //从顶点着色器接收颜色数据

out vec4 color; //把color输出到帧缓冲的第0个颜色附件（通常就是屏幕）

void main(void)
{
	color = varyingColor;
}