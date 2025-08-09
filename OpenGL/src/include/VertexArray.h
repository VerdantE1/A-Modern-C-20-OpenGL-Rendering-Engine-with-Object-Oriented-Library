#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Utility.h"

/*
This is VertexArrayObject,which is used to manage Vertex Buffer Objects (VBOs) and Index Buffer Objects (IBOs).
VBOs is just a buffer which has no semantic meaning, it just stores data.Also does IBOs.
VAOs is used to control how the data in VBOs and IBOs interpreted by the GPU.

Also,Bind and Unbind are used to set the the VAO state as current in OpenGL or not.

*/




class VertexArray :public Resource {
public:
	VertexArray();
	~VertexArray();
	void Bind() const;
	void Unbind() const;
	void LinkBufferAndLayout(const VertexBuffer& vb,const VertexBufferLayout& layout);

private:
	// Add this line to define m_id, inherited from Resource
	// unsigned int m_id; // Already inherited from Resource, no need to redefine
};    
    // No changes needed here, m_id is inherited from Resource


