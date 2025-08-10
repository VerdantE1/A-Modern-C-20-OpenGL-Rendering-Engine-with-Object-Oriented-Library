#shader vertex 
#version 330 core   
layout (location = 0) in vec3 position; //从位于Buffer里的顶点属性槽0读取数据。
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(position ,1.0); //gl_Position是一个内置变量(built-in variable)，表示顶点在裁剪空间中的位置。
	ourColor = color;
	TexCoord = texCoord;
};


#shader fragment 
#version 330 core
in vec3 ourColor; //坐标传来的,我们现在没用它
in vec2 TexCoord;


layout (location = 0) out vec4 color;  //把color输出到帧缓冲的第0个颜色附件（通常就是屏幕）

/* CPU 给的值 */
uniform vec4 u_Color;   
uniform sampler2D u_Texture1; 
uniform sampler2D u_Texture2; 


void main()
{
	//vec4 texColor = texture(u_Texture1,TexCoord);
	vec4 texColor = mix(texture(u_Texture1, TexCoord), texture(u_Texture2, TexCoord), 0.5);
	color = texColor * u_Color; //将uniform变量u_Color的值赋给输出颜色变量color。

};


