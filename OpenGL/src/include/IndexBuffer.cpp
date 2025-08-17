#pragma once
#include "IndexBuffer.h"
#include "Utility.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) :m_Count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	GLCall(glGenBuffers(1, &m_id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));


}

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& data)
{
	m_Count = static_cast<unsigned int>(data.size());
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	GLCall(glGenBuffers(1, &m_id)); // Generate a new buffer object and store its ID in m_id
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id)); // Bind the buffer to the GL_ELEMENT_ARRAY_BUFFER target
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), data.data(), GL_STATIC_DRAW)); // Upload the data to the GPU
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_id)); // Delete the buffer object from GPU memory
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id)); // Bind the buffer to the GL_ARRAY_BUFFER target
	// Note: The buffer is already bound in the constructor, so this is just a safety measure.
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // Unbind the buffer by binding to 0

}
