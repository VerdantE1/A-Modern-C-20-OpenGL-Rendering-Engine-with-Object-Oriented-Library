#version 430
// ָ�� GLSL �İ汾Ϊ 4.30

out vec4 color;
// �����������ʾƬ�ε�������ɫ

uniform mat4 mv_matrix;
// uniform ������ģ��-��ͼ����δʹ�ã�

uniform mat4 proj_matrix;
// uniform ������ͶӰ����δʹ�ã�

void main(void)
// ������������Ƭ�ε�������ɫ
{
    color = vec4(1.0, 0.0, 0.0, 1.0);
    // ��Ƭ����ɫ����Ϊ��ɫ��RGBA ��ʽ������ R=1.0��G=0.0��B=0.0��A=1.0����ȫ��͸����
}