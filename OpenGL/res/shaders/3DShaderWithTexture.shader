#shader vertex
#version 430
layout(location = 0) in vec3 position; //��λ��Buffer��Ķ������Բ�0��ȡ���ݡ�
layout(location = 1) in vec2 texCoord;


uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec4 varyingColor;
out vec2 tc;

void main(void)
{
	gl_Position = proj_matrix * mv_matrix * vec4(position.x, position.y, position.z, 1.0);
	varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 1.0); // ��λ��ӳ�䵽��ɫ
	tc = texCoord; // ���������괫�ݸ�Ƭ����ɫ��
}



#shader fragment
#version 430

layout(binding =0) uniform sampler2D textureSampler; //������Ԫ0
in vec2 tc;											//�Ӷ�����ɫ��������������	
in vec4 varyingColor;								//�Ӷ�����ɫ��������ɫ����
out vec4 color;										//��color�����֡����ĵ�0����ɫ������ͨ��������Ļ��
void main(void)
{
	color = texture(textureSampler,tc) ; //�������в�����ɫ�����붥����ɫ���
}