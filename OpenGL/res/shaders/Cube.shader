#shader vertex 
#version 430
layout (location = 0) in vec3 position; //��λ��Buffer��Ķ������Բ�0��ȡ���ݡ�
layout (location = 1) in vec3 color;

void main(void)
{
	gl_Position = vec4(position.x,position.y,position.z -2.0 ,1.0);
}



#shader fragment 
#version 430
out vec4 color; //��color�����֡����ĵ�0����ɫ������ͨ��������Ļ��

void main(void)
{
	color = vec4(1.0f, 0.0f, 0.0f, 1.0f); // ��ɫ
}