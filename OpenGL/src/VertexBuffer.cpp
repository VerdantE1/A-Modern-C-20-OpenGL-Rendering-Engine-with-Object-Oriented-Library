#include "VertexBuffer.h"
#include "Utility.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id)); // Bind the buffer to the GL_ARRAY_BUFFER target
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));


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
