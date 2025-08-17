#pragma once
#include <Texture.h>

class VertexArray;
class IndexBuffer;
class Shader;
class Shaper;

class Renderer
{
public:

	void Clear() const;

	//ͨ�õ���VertexArray, IndexBuffer��Shader����Ⱦ����������ΪͼԪ����Ⱦ����
	// �ú������Զ���VAO, IBO��Shader��������
	void Draw(const VertexArray& va, const IndexBuffer& ib , const Shader& shader) const;
	void Draw(const Shaper& sp, const Shader& shader) const;
	void Draw(const Shaper& sp, const Shader& shader, const Texture& texture) const; // �ú������Զ���VAO, IBO��Shader��������Ⱦǰ������

	void DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int instanceCount) const; //���û�ȷ��shader����instance��Ҫ��
	void ClearColor();

	// �Ƿ�ʹ���߿�ģʽ����Ȳ��ԣ��ɶ�д��
	mutable bool UsePolygonMode = false;
	mutable bool UseDepthTest = false;
	mutable bool UseCullFace = false;

	// �����߿�ģʽ��mode=trueΪ�߿�falseΪ��䣩
	const Renderer& SetPolygonMode(bool mode) const;

	// �����Ƿ�����Ȳ���
	const Renderer& SetDepthTest(bool enable) const;

	// �����޳��棨enable=true������front��back�ֱ��ʾ�Ƿ��޳�ǰ��ͺ��棩
	const Renderer& SetCullFace(bool enable ,bool front=false, bool back = true) const;
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
