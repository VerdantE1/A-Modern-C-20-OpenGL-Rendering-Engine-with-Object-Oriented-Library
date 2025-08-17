#pragma once
#include "Resource.h"
#include <vector>
/*
This class represents an OpenGL Index Buffer Object (IBO).
It is used to store indices that define the order in which Vertex Array Object are drawn.
Also, it transfers the indices stored in CPU to the GPU memory.


*/

class IndexBuffer : public Resource
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	IndexBuffer(const std::vector<unsigned int>& data);

	IndexBuffer(IndexBuffer&& other) noexcept
	{
		if(this != &other) {
			Resource::operator=(std::move(other)); // Move base class
			m_Count = other.m_Count; // Move count
			other.m_Count = 0; // Reset the count of the moved-from object
		}
	}

	IndexBuffer& operator=(IndexBuffer&& other) noexcept
	{
		if (this != &other) {
			Resource::operator=(std::move(other)); // Move base class
			m_Count = other.m_Count; // Move count
			other.m_Count = 0; // Reset the count of the moved-from object
		}
		return *this;
	}

	~IndexBuffer() override;

	void Bind() const override;
	void Unbind() const override;
	inline unsigned int GetCount() const { return m_Count; } // Returns the number of indices in the buffer

private:
	unsigned int m_Count;

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
