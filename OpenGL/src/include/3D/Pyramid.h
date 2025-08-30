#include "Shaper.h"
#include "Renderer.h"

class Pyramid : public Shaper
{
    inline static constexpr float vertices[] = {
        // 位置坐标              // 纹理坐标    // 法线坐标
        
        // 底面 (Y = -1, 法线: 0, -1, 0) - 4个顶点
        -1.0f, -1.0f,  1.0f,    0.0f, 0.0f,   0.0f, -1.0f, 0.0f, // 前左
         1.0f, -1.0f,  1.0f,    1.0f, 0.0f,   0.0f, -1.0f, 0.0f, // 前右
         1.0f, -1.0f, -1.0f,    1.0f, 1.0f,   0.0f, -1.0f, 0.0f, // 后右
        -1.0f, -1.0f, -1.0f,    0.0f, 1.0f,   0.0f, -1.0f, 0.0f, // 后左
        
        // 前面三角形 (法线计算: 向外法线约为 0, 0.447, 0.894)
         0.0f,  1.0f,  0.0f,    0.5f, 0.0f,   0.0f, 0.447f, 0.894f, // 顶点
        -1.0f, -1.0f,  1.0f,    0.0f, 1.0f,   0.0f, 0.447f, 0.894f, // 左下
         1.0f, -1.0f,  1.0f,    1.0f, 1.0f,   0.0f, 0.447f, 0.894f, // 右下
        
        // 右面三角形 (法线: 0.894, 0.447, 0)
         0.0f,  1.0f,  0.0f,    0.5f, 0.0f,   0.894f, 0.447f, 0.0f, // 顶点  
         1.0f, -1.0f,  1.0f,    0.0f, 1.0f,   0.894f, 0.447f, 0.0f, // 前下
         1.0f, -1.0f, -1.0f,    1.0f, 1.0f,   0.894f, 0.447f, 0.0f, // 后下
        
        // 后面三角形 (法线: 0, 0.447, -0.894)
         0.0f,  1.0f,  0.0f,    0.5f, 0.0f,   0.0f, 0.447f, -0.894f, // 顶点
         1.0f, -1.0f, -1.0f,    0.0f, 1.0f,   0.0f, 0.447f, -0.894f, // 右下
        -1.0f, -1.0f, -1.0f,    1.0f, 1.0f,   0.0f, 0.447f, -0.894f, // 左下
        
        // 左面三角形 (法线: -0.894, 0.447, 0)
         0.0f,  1.0f,  0.0f,    0.5f, 0.0f,   -0.894f, 0.447f, 0.0f, // 顶点
        -1.0f, -1.0f, -1.0f,    0.0f, 1.0f,   -0.894f, 0.447f, 0.0f, // 后下
        -1.0f, -1.0f,  1.0f,    1.0f, 1.0f,   -0.894f, 0.447f, 0.0f, // 前下
    };
    
    inline static constexpr unsigned int indices[] = {
        // 底面 (两个三角形)
        0, 1, 2,    // 底面三角形1
        2, 3, 0,    // 底面三角形2
        
        // 侧面 (4个三角形)
        4, 5, 6,    // 前面
        7, 8, 9,    // 右面
        10, 11, 12, // 后面
        13, 14, 15  // 左面
    };

public:
    Pyramid() :
        Shaper(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(unsigned int), { (float)3, (float)2, (float)3 })  // 🆕 位置3 + 纹理2 + 法线3
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
