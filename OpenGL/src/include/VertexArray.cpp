#include "VertexArray.h"



void VertexArray::LinkBufferAndLayout(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	vb.Bind(); 
	const auto& elements = layout.GetElements(); // Get the vertex buffer layout elements)
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		GLCall(glEnableVertexAttribArray(i)); //Enable Context for the vertex attribute array at index i
		GLCall(glVertexAttribPointer(
			i, 
			elements[i].a_count,
			elements[i].type, 
			elements[i].normalized,
			layout.GetStride(),
			(const void*)offset)
		);
		offset += elements[i].a_count * VertexLayoutElement::GetSizeOfType(elements[i].type); 
	}
}


void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0)); // Unbind the Vertex Array Object (VAO) from the current context
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_id)); // Bind the VAO to the current context
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_id)); // Delete the Vertex Array Object (VAO) when it is no longer needed
	m_id = 0; // Reset the ID to 0 after deletion

}


VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_id)); // Generate a Vertex Array Object (VAO) to store the vertex attribute state
	GLCall(glBindVertexArray(m_id)); // Bind the VAO to the current context
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
