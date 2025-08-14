#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_TexCoord;

out vec3 v_Color;
out vec2 v_TexCoord;

uniform mat4 u_ModelMatrix;

void main()
{
    v_Color = a_Color;
    v_TexCoord = a_TexCoord;
    gl_Position = u_ModelMatrix * vec4(a_Position, 1.0);
}








#shader fragment
#version 330 core

in vec3 v_Color;
in vec2 v_TexCoord;

layout(location = 0) out vec4 FragColor;

uniform vec4 u_Color;           // 通用颜色
uniform sampler2D u_Texture1;   // 可选纹理1
uniform bool u_UseTexture;      // 是否使用纹理

void main()
{
    vec4 baseColor = vec4(v_Color, 1.0) * u_Color;
    if (u_UseTexture)
    {
        vec4 texColor = texture(u_Texture1, v_TexCoord);
        FragColor = texColor * u_Color;
    }
    else
    {
        FragColor = baseColor;
    }
}