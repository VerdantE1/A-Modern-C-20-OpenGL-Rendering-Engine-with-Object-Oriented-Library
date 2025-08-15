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