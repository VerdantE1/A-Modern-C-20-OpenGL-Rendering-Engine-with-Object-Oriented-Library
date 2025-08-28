#include "Shaper.h"
#include "Renderer.h"

class Pyramid :public Shaper
{
	inline static constexpr float vertices[] = {
		// 顶点位置                // 纹理坐标
		// 注意: 为每个三角形的每个顶点单独定义纹理坐标
		
		// 顶点(用于所有侧面)
		 0.0f,  1.0f, 0.0f,      0.5f, 0.0f,   // 顶点 (索引0)
		
		// 底面顶点 - 每个顶点有不同的纹理坐标，适合底面映射
		-1.0f, -1.0f, 1.0f,      0.0f, 0.0f,   // 底面左前 (索引1)
		 1.0f, -1.0f, 1.0f,      1.0f, 0.0f,   // 底面右前 (索引2)
		 1.0f, -1.0f, -1.0f,     1.0f, 1.0f,   // 底面右后 (索引3)
		-1.0f, -1.0f, -1.0f,     0.0f, 1.0f,   // 底面左后 (索引4)
		
		// 侧面顶点 - 每个侧面的底边顶点使用不同的纹理坐标
		// 前面
		-1.0f, -1.0f, 1.0f,      0.0f, 1.0f,   // 前面左下 (索引5)
		 1.0f, -1.0f, 1.0f,      1.0f, 1.0f,   // 前面右下 (索引6)
		
		// 右面
		 1.0f, -1.0f, 1.0f,      0.0f, 1.0f,   // 右面左下 (索引7)
		 1.0f, -1.0f, -1.0f,     1.0f, 1.0f,   // 右面右下 (索引8)
		
		// 后面
		 1.0f, -1.0f, -1.0f,     0.0f, 1.0f,   // 后面左下 (索引9)
		-1.0f, -1.0f, -1.0f,     1.0f, 1.0f,   // 后面右下 (索引10)
		
		// 左面
		-1.0f, -1.0f, -1.0f,     0.0f, 1.0f,   // 左面左下 (索引11)
		-1.0f, -1.0f, 1.0f,      1.0f, 1.0f,   // 左面右下 (索引12)
	};
	
	// 使用新的索引，对应于顶点数组中的位置
	inline static constexpr unsigned int indices[] = {
		1, 2, 3,	// 底面三角形1
		3, 4, 1,    // 底面三角形2
		0, 5, 6,	// 前面
		0, 7, 8,	// 右面
		0, 9, 10, 	// 后面
		0, 11, 12	// 左面
	};

public:
	Pyramid() :
		Shaper(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(unsigned int), { (float)3, (float)2 })
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
