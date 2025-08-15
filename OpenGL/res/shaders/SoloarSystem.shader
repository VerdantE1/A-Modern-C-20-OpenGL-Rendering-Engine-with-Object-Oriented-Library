#shader vertex 
#version 430
layout (location = 0) in vec3 position; //��λ��Buffer��Ķ������Բ�0��ȡ���ݡ�
layout (location = 1) in vec3 color;


//uniform mat4 mv_matrix; 
//uniform mat4 proj_matrix;
uniform mat4 mvp_matrix; //ģ����ͼͶӰ����
out vec4 varyingColor;
void main(void)
{
	gl_Position =  mvp_matrix * vec4(position.x,position.y,position.z ,1.0);
	varyingColor = vec4(position,1.0) * 0.5 + vec4(0.5,0.5,0.5,1.0); // ��λ��ӳ�䵽��ɫ
}



#shader fragment 
#version 430

in vec4 varyingColor; //�Ӷ�����ɫ��������ɫ����

out vec4 color; //��color�����֡����ĵ�0����ɫ������ͨ��������Ļ��

void main(void)
{
	color = varyingColor;
}