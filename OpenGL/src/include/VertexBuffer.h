#pragma once
#include "Resource.h"
/*
This class represents a Vertex Buffer Object(VBO) in OpenGL.
It receive vertex "data" and "size" during construction, the data stored in CPU memory will be copied to GPU memory.
The OpenGL will generate a unique ID for the VBO, which can be used to bind and unbind the buffer, after construction.
Binding the VBO will make it the current active buffer for the OpenGl Context.Unbinding the VBO will make no buffer active.

*/ 


class VertexBuffer : public Resource
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer() override;

	void Bind() const override;
	void Unbind() const override;


};