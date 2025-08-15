#shader vertex 
#version 430
layout (location = 0) in vec3 position; //从位于Buffer里的顶点属性槽0读取数据。
layout (location = 1) in vec3 color;
uniform mat4 u_ProjMatrix;
uniform mat4 u_MvMatrix;
void main(void)
{
	gl_Position = u_ProjMatrix * u_MvMatrix * vec4(position.x,position.y,position.z ,1.0);
}



#shader fragment 
#version 430
out vec4 color; //把color输出到帧缓冲的第0个颜色附件（通常就是屏幕）

void main(void)
{
	color = vec4(1.0f, 0.0f, 0.0f, 1.0f); // 红色
}