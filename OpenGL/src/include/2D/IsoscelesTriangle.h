#pragma once
#include "Shaper.h"
#include "Renderer.h"

class IsoscelesTriangle : public Shaper {
    static constexpr GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // 红色
       -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // 绿色
       0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f  // 蓝色
    };
public:
    // 构造函数：可选参数控制底边宽度和高度
    IsoscelesTriangle():
        Shaper(vertices, sizeof(vertices)/sizeof(vertices[0]), nullptr, 0, {(float)3, (float)3})
    {
        va.LinkBufferAndLayout(vb, layout);
	}


    void Draw(Shader& shader, const Renderer& renderer) override {
		renderer.Clear();
        BindAll(va, shader);
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
    }

private:
};