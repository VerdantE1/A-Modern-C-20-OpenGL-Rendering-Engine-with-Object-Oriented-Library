#shader vertex 
#version 430
layout (location = 0) in vec3 position; //��λ��Buffer��Ķ������Բ�0��ȡ���ݡ�
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

uniform mat4 u_MvMatrix; //MV����
uniform mat4 u_ProjMatrix; //ͶӰ����

void main(void)
{
	//gl_Position = u_ProjMatrix * u_MvMatrix * vec4(position,1.0); //������λ��ת��Ϊ�ü��ռ�����
	gl_Position = vec4(position,1.0);
}



#shader fragment 
#version 430
layout(location =0) out vec4 color; //��color�����֡����ĵ�0����ɫ������ͨ��������Ļ��

void main(void)
{
	color = vec4(0.0, 1.0, 0.0, 1.0); // ��ʾȫ��ɫ
}