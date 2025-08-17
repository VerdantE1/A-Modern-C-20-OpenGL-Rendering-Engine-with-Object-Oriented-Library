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