#shader vertex 
#version 430
layout (location = 0) in vec3 position; //��λ��Buffer��Ķ������Բ�0��ȡ���ݡ�
layout (location = 1) in vec2 texCoord;



uniform mat4 mvp_matrix; //ģ����ͼͶӰ����

out vec4 varyingColor;
out vec2 tc;
void main(void)
{
	gl_Position =  mvp_matrix * vec4(position.x,position.y,position.z ,1.0);
	varyingColor = vec4(position,1.0) * 0.5 + vec4(0.5,0.5,0.5,1.0); // ��λ��ӳ�䵽��ɫ
	tc = texCoord;  // �ؼ���һ��
}



#shader fragment 
#version 430

in vec4 varyingColor; //�Ӷ�����ɫ��������ɫ����
in vec2 tc;

out vec4 color; //��color�����֡����ĵ�0����ɫ������ͨ��������Ļ��


layout(binding = 0) uniform sampler2D sunSampler;
layout(binding = 1) uniform sampler2D earthSampler;
layout(binding = 2) uniform sampler2D moonSampler;

uniform int objectType; 

void main(void)
{
    if(objectType == 0)
        color = texture(sunSampler, tc);
    else if(objectType == 1)
        color = texture(earthSampler, tc);
    else if(objectType == 2)
        color = texture(moonSampler, tc);
    else
        color = vec4(1,0,1,1);
}