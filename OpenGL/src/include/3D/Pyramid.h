#include "Shaper.h"
#include "Renderer.h"

class Pyramid :public Shaper
{
	inline static constexpr float vertices[] = {
		// ����λ��                // ��������
		// ע��: Ϊÿ�������ε�ÿ�����㵥��������������
		
		// ����(�������в���)
		 0.0f,  1.0f, 0.0f,      0.5f, 0.0f,   // ���� (����0)
		
		// ���涥�� - ÿ�������в�ͬ���������꣬�ʺϵ���ӳ��
		-1.0f, -1.0f, 1.0f,      0.0f, 0.0f,   // ������ǰ (����1)
		 1.0f, -1.0f, 1.0f,      1.0f, 0.0f,   // ������ǰ (����2)
		 1.0f, -1.0f, -1.0f,     1.0f, 1.0f,   // �����Һ� (����3)
		-1.0f, -1.0f, -1.0f,     0.0f, 1.0f,   // ������� (����4)
		
		// ���涥�� - ÿ������ĵױ߶���ʹ�ò�ͬ����������
		// ǰ��
		-1.0f, -1.0f, 1.0f,      0.0f, 1.0f,   // ǰ������ (����5)
		 1.0f, -1.0f, 1.0f,      1.0f, 1.0f,   // ǰ������ (����6)
		
		// ����
		 1.0f, -1.0f, 1.0f,      0.0f, 1.0f,   // �������� (����7)
		 1.0f, -1.0f, -1.0f,     1.0f, 1.0f,   // �������� (����8)
		
		// ����
		 1.0f, -1.0f, -1.0f,     0.0f, 1.0f,   // �������� (����9)
		-1.0f, -1.0f, -1.0f,     1.0f, 1.0f,   // �������� (����10)
		
		// ����
		-1.0f, -1.0f, -1.0f,     0.0f, 1.0f,   // �������� (����11)
		-1.0f, -1.0f, 1.0f,      1.0f, 1.0f,   // �������� (����12)
	};
	
	// ʹ���µ���������Ӧ�ڶ��������е�λ��
	inline static constexpr unsigned int indices[] = {
		1, 2, 3,	// ����������1
		3, 4, 1,    // ����������2
		0, 5, 6,	// ǰ��
		0, 7, 8,	// ����
		0, 9, 10, 	// ����
		0, 11, 12	// ����
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
