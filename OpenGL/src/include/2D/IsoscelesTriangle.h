#pragma once
#include "Shaper.h"

class IsoscelesTriangle : public Shaper {
    static constexpr GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // ��ɫ
       -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // ��ɫ
       0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f  // ��ɫ
    };
public:
    // ���캯������ѡ�������Ƶױ߿�Ⱥ͸߶�
    IsoscelesTriangle():vb(vertices, sizeof(vertices)),
                              layout({ (float)3, (float)3 }) 
    {
        va.LinkBufferAndLayout(vb, layout);
	}


    void Draw(Shader& shader,Renderer & renderer) override {
		renderer.Clear();
        BindAll(va, shader);
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
    }

private:
    VertexBuffer vb;
    VertexBufferLayout layout;
};