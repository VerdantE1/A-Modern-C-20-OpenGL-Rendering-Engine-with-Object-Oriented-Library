#include "Renderer.h"
#include "Utility.h"
#include "IndexBuffer.h"
#include "Shaper.h"

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::ClearColor()
{
	GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f)); // 设置背景为一个深灰色调色
}

const Renderer& Renderer::SetPolygonMode(bool mode) const
{
	if (mode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 线框
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 填充
	return (*this);
}

const Renderer& Renderer::SetDepthTest(bool enable) const
{
	if (enable)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	return (*this);
}

const Renderer& Renderer::SetCullFace(bool enable, bool front, bool back) const
{
	if (enable)
	{
		glEnable(GL_CULL_FACE);
		if (front && back)
			glCullFace(GL_FRONT_AND_BACK); // 启用双面剔除
		else if (front)
			glCullFace(GL_FRONT); // 只剔除前面
		else if (back)
			glCullFace(GL_BACK); // 只剔除后面
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}
	return (*this);
}

const Renderer& Renderer::SetBlend(bool enable) const
{
	if (enable)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
	return (*this);
}

// ===== 原有的索引渲染方法 =====
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	BindAll(va, ib, shader);
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, (void*)0)); 
}

void Renderer::Draw(const Shaper& sp, const Shader& shader) const
{
	Draw(sp.GetVertexArray(), sp.GetIndexBuffer(), shader);
}

void Renderer::Draw(const Shaper& sp, const Shader& shader, const Texture& texture) const
{
	BindAll(sp.GetVertexArray(), sp.GetIndexBuffer(), shader, texture);
	GLCall(glDrawElements(GL_TRIANGLES, sp.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, (void*)0));
}

void Renderer::DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int instanceCount) const
{
	BindAll(va, ib, shader);
	GLCall(glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, (void*)0, instanceCount));
}

// ===== 新增的全展开顶点渲染方法 =====
void Renderer::DrawArrays(const VertexArray& va, const Shader& shader, unsigned int vertexCount) const
{
	BindAll(va, shader);
	GLCall(glDrawArrays(GL_TRIANGLES, 0, vertexCount));
}

void Renderer::DrawArrays(const VertexArray& va, const Shader& shader, const Texture& texture, unsigned int vertexCount) const
{
	BindAll(va, shader, texture);
	GLCall(glDrawArrays(GL_TRIANGLES, 0, vertexCount));
}


void Renderer::DrawArraysInstanced(const VertexArray& va, const Shader& shader, unsigned int vertexCount, unsigned int instanceCount) const
{
	BindAll(va, shader);
	GLCall(glDrawArraysInstanced(GL_TRIANGLES, 0, vertexCount, instanceCount));
}

void Renderer::DrawArrays(const Shaper& sp, const Shader& shader, unsigned int vertexCount) const
{
	BindAll(sp.GetVertexArray(), shader);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void Renderer::DrawArrays(const Shaper& sp, const Shader& shader, const Texture& texture, unsigned int vertexCount) const
{
	BindAll(sp.GetVertexArray(), shader, texture);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

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
