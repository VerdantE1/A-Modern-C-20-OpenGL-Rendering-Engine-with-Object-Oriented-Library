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
void main()
{
	color = vec4(1.0, 0.3 ,0.8 , 1.0);
};