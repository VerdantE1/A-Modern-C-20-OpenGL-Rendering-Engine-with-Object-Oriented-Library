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

	// ===== 原有的索引渲染方法 =====
	// 通用的用VertexArray, IndexBuffer和Shader进行渲染，这里主要为图元进行渲染设置
	// 该函数会自动绑定VAO, IBO和Shader，并进行设置
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Draw(const Shaper& sp, const Shader& shader) const;
	void Draw(const Shaper& sp, const Shader& shader, const Texture& texture) const; // 该函数会自动绑定VAO, IBO和Shader，并进行渲染前设置

	void DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int instanceCount) const; // 需要用户确保shader包含instance相关

	// ===== 新增的全展开顶点渲染方法 =====
	// 用于渲染完全展开的顶点数据（不使用索引缓冲）
	void DrawArrays(const VertexArray& va, const Shader& shader, unsigned int vertexCount) const;
	void DrawArrays(const VertexArray& va, const Shader& shader, const Texture& texture, unsigned int vertexCount) const;
	void DrawArrays(const Shaper& sp, const Shader& shader, unsigned int vertexCount) const;
	void DrawArrays(const Shaper& sp, const Shader& shader, const Texture& texture, unsigned int vertexCount) const;

	
	// 实例化渲染的数组版本
	void DrawArraysInstanced(const VertexArray& va, const Shader& shader, unsigned int vertexCount, unsigned int instanceCount) const;

	void ClearColor();

	// 是否使用线框模式和深度测试，可读写的
	mutable bool UsePolygonMode = false;
	mutable bool UseDepthTest = false;
	mutable bool UseCullFace = false;

	// 设置线框模式（mode=true为线框false为填充）
	const Renderer& SetPolygonMode(bool mode) const;

	// 设置是否启用深度测试
	const Renderer& SetDepthTest(bool enable) const;

	// 设置背面剔除（enable=true启用，front和back分别表示是否剔除前面和后面）
	const Renderer& SetCullFace(bool enable, bool front=false, bool back = true) const;

	const Renderer& SetBlend(bool enable) const;
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
