#include "VertexBuffer.h"
#include "Utility.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id)); // Bind the buffer to the GL_ARRAY_BUFFER target
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));


}

VertexBuffer::VertexBuffer(const std::vector<float>& data)
{
	unsigned int size = static_cast<unsigned int>(data.size() * sizeof(float));
	GLCall(glGenBuffers(1, &m_id)); // Generate a new buffer object and store its ID in m_id
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id)); // Bind the buffer to the GL_ARRAY_BUFFER target
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data.data(), GL_STATIC_DRAW)); // Upload the data to the GPU

}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_id)); // Delete the buffer object from GPU memory
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id)); // Bind the buffer to the GL_ARRAY_BUFFER target
	// Note: The buffer is already bound in the constructor, so this is just a safety measure.
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Unbind the buffer by binding to 0

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
