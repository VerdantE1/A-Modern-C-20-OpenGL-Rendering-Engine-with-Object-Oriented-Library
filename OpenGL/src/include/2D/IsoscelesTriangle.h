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
/*
 * Copyright (c) 2025 
 * Email: 2523877046@qq.com
 * Author: Baiqiang Long (Buzzlight)
 * 
 * This file is part of the ReduxGL project.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
