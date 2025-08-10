#shader vertex 
#version 330 core   
layout (location = 0) in vec3 position; //��λ��Buffer��Ķ������Բ�0��ȡ���ݡ�
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(position ,1.0); //gl_Position��һ�����ñ���(built-in variable)����ʾ�����ڲü��ռ��е�λ�á�
	ourColor = color;
	TexCoord = texCoord;
};


#shader fragment 
#version 330 core
in vec3 ourColor; //���괫����,��������û����
in vec2 TexCoord;


layout (location = 0) out vec4 color;  //��color�����֡����ĵ�0����ɫ������ͨ��������Ļ��

/* CPU ����ֵ */
uniform vec4 u_Color;   
uniform sampler2D u_Texture1; 
uniform sampler2D u_Texture2; 


void main()
{
	//vec4 texColor = texture(u_Texture1,TexCoord);
	vec4 texColor = mix(texture(u_Texture1, TexCoord), texture(u_Texture2, TexCoord), 0.5);
	color = texColor * u_Color; //��uniform����u_Color��ֵ���������ɫ����color��

};


