#pragma once
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <Shader.h>
#include <Utility.h>
#include <Texture.h>

class Renderer
{
public:

	void Clear();
	void Draw(const VertexArray& va, const IndexBuffer& ib , const Shader& shader) const;
	void ClearColor();



private:
};