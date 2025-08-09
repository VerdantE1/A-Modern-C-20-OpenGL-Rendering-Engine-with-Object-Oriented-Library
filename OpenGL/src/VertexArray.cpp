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
