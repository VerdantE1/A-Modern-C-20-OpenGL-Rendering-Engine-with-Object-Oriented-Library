#pragma once
#include "Shaper.h"
#include "Renderer.h"

class Cube : public Shaper {
    inline static constexpr float vertices[] = {
        // 位置坐标              // 纹理坐标    // 法线坐标
        // 前面 (Z = 1, 法线: 0, 0, 1)
        -1.0f, -1.0f,  1.0f,    0.0f, 0.0f,   0.0f, 0.0f, 1.0f,  // 左下
         1.0f, -1.0f,  1.0f,    1.0f, 0.0f,   0.0f, 0.0f, 1.0f,  // 右下
         1.0f,  1.0f,  1.0f,    1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  // 右上
        -1.0f,  1.0f,  1.0f,    0.0f, 1.0f,   0.0f, 0.0f, 1.0f,  // 左上

        // 后面 (Z = -1, 法线: 0, 0, -1)  
        -1.0f, -1.0f, -1.0f,    1.0f, 0.0f,   0.0f, 0.0f, -1.0f, // 右下
         1.0f, -1.0f, -1.0f,    0.0f, 0.0f,   0.0f, 0.0f, -1.0f, // 左下
         1.0f,  1.0f, -1.0f,    0.0f, 1.0f,   0.0f, 0.0f, -1.0f, // 左上
        -1.0f,  1.0f, -1.0f,    1.0f, 1.0f,   0.0f, 0.0f, -1.0f, // 右上

        // 右面 (X = 1, 法线: 1, 0, 0)
         1.0f, -1.0f,  1.0f,    0.0f, 0.0f,   1.0f, 0.0f, 0.0f,  // 前下
         1.0f, -1.0f, -1.0f,    1.0f, 0.0f,   1.0f, 0.0f, 0.0f,  // 后下
         1.0f,  1.0f, -1.0f,    1.0f, 1.0f,   1.0f, 0.0f, 0.0f,  // 后上
         1.0f,  1.0f,  1.0f,    0.0f, 1.0f,   1.0f, 0.0f, 0.0f,  // 前上

        // 左面 (X = -1, 法线: -1, 0, 0)
        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,   -1.0f, 0.0f, 0.0f, // 后下
        -1.0f, -1.0f,  1.0f,    1.0f, 0.0f,   -1.0f, 0.0f, 0.0f, // 前下
        -1.0f,  1.0f,  1.0f,    1.0f, 1.0f,   -1.0f, 0.0f, 0.0f, // 前上
        -1.0f,  1.0f, -1.0f,    0.0f, 1.0f,   -1.0f, 0.0f, 0.0f, // 后上

        // 上面 (Y = 1, 法线: 0, 1, 0)
        -1.0f,  1.0f,  1.0f,    0.0f, 0.0f,   0.0f, 1.0f, 0.0f,  // 前左
         1.0f,  1.0f,  1.0f,    1.0f, 0.0f,   0.0f, 1.0f, 0.0f,  // 前右
         1.0f,  1.0f, -1.0f,    1.0f, 1.0f,   0.0f, 1.0f, 0.0f,  // 后右
        -1.0f,  1.0f, -1.0f,    0.0f, 1.0f,   0.0f, 1.0f, 0.0f,  // 后左

        // 下面 (Y = -1, 法线: 0, -1, 0)
        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,   0.0f, -1.0f, 0.0f, // 后左
         1.0f, -1.0f, -1.0f,    1.0f, 0.0f,   0.0f, -1.0f, 0.0f, // 后右
         1.0f, -1.0f,  1.0f,    1.0f, 1.0f,   0.0f, -1.0f, 0.0f, // 前右
        -1.0f, -1.0f,  1.0f,    0.0f, 1.0f,   0.0f, -1.0f, 0.0f, // 前左
    };

    inline static constexpr unsigned int indices[] = {
        // 前面
        0, 1, 2, 2, 3, 0,
        // 后面
        4, 5, 6, 6, 7, 4,
        // 右面
        8, 9, 10, 10, 11, 8,
        // 左面
        12, 13, 14, 14, 15, 12,
        // 上面
        16, 17, 18, 18, 19, 16,
        // 下面
        20, 21, 22, 22, 23, 20
    };

public:
    Cube():
        Shaper(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(unsigned int), {(float)3, (float)2, (float)3})  // 🆕 位置3 + 纹理2 + 法线3
    {
        va.LinkBufferAndLayout(vb, layout);
    }

    void Draw(Shader& shader, const Renderer& renderer) override {
        renderer.Draw(va, ib, shader);
    }
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
