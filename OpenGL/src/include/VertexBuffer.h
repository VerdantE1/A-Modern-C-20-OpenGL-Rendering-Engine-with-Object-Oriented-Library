#pragma once
#include "Resource.h"
#include <vector>
/*
This class represents a Vertex Buffer Object(VBO) in OpenGL.
It receive vertex "data" and "size" during construction, the data stored in CPU memory will be copied to GPU memory.
The OpenGL will generate a unique ID for the VBO, which can be used to bind and unbind the buffer, after construction.
Binding the VBO will make it the current active buffer for the OpenGl Context.Unbinding the VBO will make no buffer active.

*/ 


class VertexBuffer : public Resource
{
public:
	VertexBuffer() = default;
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(const std::vector<float>& data);

	// 添加移动语义支持
	VertexBuffer(VertexBuffer&& other) noexcept = default;
	VertexBuffer& operator=(VertexBuffer&& other) noexcept = default;

	~VertexBuffer() override;

	void Bind() const override;
	void Unbind() const override;


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
