#version 430
// ָ�� GLSL �İ汾Ϊ 4.30

layout (location=0) in vec3 position;
// �����������ʾ�������άλ�ã��󶨵� location = 0

uniform mat4 mv_matrix;
// uniform ��������ʾģ��-��ͼ�������ڽ������ģ�Ϳռ�任����ͼ�ռ�

uniform mat4 proj_matrix;
// uniform ��������ʾͶӰ�������ڽ��������ͼ�ռ�任���ü��ռ�

void main(void)
// �����������㶥�������λ��
{
    gl_Position = proj_matrix * mv_matrix * vec4(position,1.0);
    // ������λ�ô�ģ�Ϳռ����α任����ͼ�ռ�Ͳü��ռ�
    // ���ս���洢�����ñ��� gl_Position �У����ں����Ĺ�դ���׶�
}