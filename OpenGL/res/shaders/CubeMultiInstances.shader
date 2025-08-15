#shader vertex 
#version 430
layout (location = 0) in vec3 position; //从位于Buffer里的顶点属性槽0读取数据。
layout (location = 1) in vec3 color;


uniform mat4 v_matrix; 
uniform mat4 proj_matrix; 
uniform float tf; 


out vec4 varyingColor;

mat4 buildRotateX(float rad);     // 矩阵变换工具函数的声明 
mat4 buildRotateY(float rad);     // GLSL 要求函数先声明后调用 
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


   // 构建模型矩阵，然后构建MV矩阵 
	mat4 newM_matrix = localTrans * localRotX * localRotY * localRotZ; 
	mat4 mv_matrix =  v_matrix * newM_matrix;

	gl_Position = proj_matrix * mv_matrix * vec4(position.x,position.y,position.z ,1.0);
	varyingColor = vec4(position,1.0) * 0.5 + vec4(0.5,0.5,0.5,1.0); // 将位置映射到颜色
}

// 构建并返回平移矩阵 
mat4 buildTranslate(float x, float y, float z)
{
    mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        x, y, z, 1.0);
    return trans;
}
// 构建并返回绕x轴的旋转矩阵 
mat4 buildRotateX(float rad)
{
    mat4 xrot = mat4(1.0, 0.0, 0.0, 0.0,
        0.0, cos(rad), -sin(rad), 0.0,
        0.0, sin(rad), cos(rad), 0.0,
        0.0, 0.0, 0.0, 1.0);
    return xrot;
}
// 构建并返回绕y轴的旋转矩阵 
mat4 buildRotateY(float rad)
{
    mat4 yrot = mat4(cos(rad), 0.0, sin(rad), 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sin(rad), 0.0, cos(rad), 0.0,
        0.0, 0.0, 0.0, 1.0);
    return yrot;
}
// 构建并返回绕z轴的旋转矩阵 
mat4 buildRotateZ(float rad)
{
    mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
        sin(rad), cos(rad), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0);
    return zrot;
}
// 构建并返回缩放矩阵 
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

in vec4 varyingColor; //从顶点着色器接收颜色数据

out vec4 color; //把color输出到帧缓冲的第0个颜色附件（通常就是屏幕）

void main(void)
{
	color = varyingColor;
}