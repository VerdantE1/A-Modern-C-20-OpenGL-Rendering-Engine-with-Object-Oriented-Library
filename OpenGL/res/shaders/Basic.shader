#shader vertex 
#version 330 core   
layout (location = 0) in vec3 position; //��λ��Buffer��Ķ������Բ�0��ȡ���ݡ�
void main()
{
	gl_Position = vec4(position.x , position.y ,position.z ,1.0); //gl_Position��һ�����ñ���(built-in variable)����ʾ�����ڲü��ռ��е�λ�á�
};


#shader fragment 
#version 330 core
layout (location = 0) out vec4 color; 

uniform vec4 u_Color; // uniform����������CPU������һ�Σ�Ȼ����GPU�˵�����Ƭ����ɫ����ʹ�á�
void main()
{
	color = u_Color; //��uniform����u_Color��ֵ���������ɫ����color��
};