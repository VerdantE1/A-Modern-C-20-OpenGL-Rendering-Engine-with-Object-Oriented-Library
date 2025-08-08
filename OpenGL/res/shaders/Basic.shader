#shader vertex 
#version 330 core   
layout (location = 0) in vec3 position; //从位于Buffer里的顶点属性槽0读取数据。
void main()
{
	gl_Position = vec4(position.x , position.y ,position.z ,1.0); //gl_Position是一个内置变量(built-in variable)，表示顶点在裁剪空间中的位置。
};


#shader fragment 
#version 330 core
layout (location = 0) out vec4 color; 

uniform vec4 u_Color; // uniform变量可以在CPU端设置一次，然后在GPU端的所有片段着色器中使用。
void main()
{
	color = u_Color; //将uniform变量u_Color的值赋给输出颜色变量color。
};