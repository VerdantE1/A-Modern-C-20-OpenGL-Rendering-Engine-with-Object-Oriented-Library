#shader vertex 
#version 430
layout (location = 0) in vec3 position; //��λ��Buffer��Ķ������Բ�0��ȡ���ݡ�
layout (location = 1) in vec3 color;


uniform mat4 v_matrix; 
uniform mat4 proj_matrix; 
uniform float tf; 


out vec4 varyingColor;

mat4 buildRotateX(float rad);     // ����任���ߺ��������� 
mat4 buildRotateY(float rad);     // GLSL Ҫ��������������� 
mat4 buildRotateZ(float rad); 
mat4 buildTranslate(float x, float y, float z); 



void main(void)
{
	float i = gl_InstanceID + tf;
    float a = sin(203.0 * i/8000.0) * 403.0; 
    float b = cos(301.0 * i/4001.0) * 401.0; 
    float c = sin(400.0 * i/6003.0) * 405.0; 

	 
   mat4 localRotX = buildRotateX(1000*i); 
   mat4 localRotY = buildRotateY(1000*i); 
   mat4 localRotZ = buildRotateZ(1000*i); 
   mat4 localTrans = buildTranslate(a,b,c); 


   // ����ģ�;���Ȼ�󹹽�MV���� 
	mat4 newM_matrix = localTrans * localRotX * localRotY * localRotZ; 
	mat4 mv_matrix =  v_matrix * newM_matrix;

	gl_Position = proj_matrix * mv_matrix * vec4(position.x,position.y,position.z ,1.0);
	varyingColor = vec4(position,1.0) * 0.5 + vec4(0.5,0.5,0.5,1.0); // ��λ��ӳ�䵽��ɫ
}

// ����������ƽ�ƾ��� 
mat4 buildTranslate(float x, float y, float z)
{
    mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        x, y, z, 1.0);
    return trans;
}
// ������������x�����ת���� 
mat4 buildRotateX(float rad)
{
    mat4 xrot = mat4(1.0, 0.0, 0.0, 0.0,
        0.0, cos(rad), -sin(rad), 0.0,
        0.0, sin(rad), cos(rad), 0.0,
        0.0, 0.0, 0.0, 1.0);
    return xrot;
}
// ������������y�����ת���� 
mat4 buildRotateY(float rad)
{
    mat4 yrot = mat4(cos(rad), 0.0, sin(rad), 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sin(rad), 0.0, cos(rad), 0.0,
        0.0, 0.0, 0.0, 1.0);
    return yrot;
}
// ������������z�����ת���� 
mat4 buildRotateZ(float rad)
{
    mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
        sin(rad), cos(rad), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0);
    return zrot;
}
// �������������ž��� 
mat4 buildScale(float x, float y, float z)
{
    mat4 scale = mat4(x, 0.0, 0.0, 0.0,
        0.0, y, 0.0, 0.0,
        0.0, 0.0, z, 0.0,
        0.0, 0.0, 0.0, 1.0);
    return scale;
}

#shader fragment 
#version 430

in vec4 varyingColor; //�Ӷ�����ɫ��������ɫ����

out vec4 color; //��color�����֡����ĵ�0����ɫ������ͨ��������Ļ��

void main(void)
{
	color = varyingColor;
}