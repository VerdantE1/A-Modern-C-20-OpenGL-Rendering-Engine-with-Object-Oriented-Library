#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"



class Renderer;

class Shaper {
public:
    //verticesSizeÊÇ×Ö½ÚÊý£¬
    Shaper(const void* vertices,unsigned int verticesSize, const unsigned int* indices, unsigned int indicesSize, std::vector<VertexBufferLayout::SupportedTypes> acnt_vec)
        : vb(vertices, verticesSize), ib(indices,indicesSize),layout(acnt_vec)
    {
        va.LinkBufferAndLayout(vb, layout);
    }
    virtual ~Shaper() = default;
    virtual void Draw(Shader& shader, const Renderer& renderer) = 0;

    const VertexArray& GetVertexArray() const { return va; }
	const VertexBuffer& GetVertexBuffer() const { return vb; }
    const IndexBuffer& GetIndexBuffer() const { return ib; }
	const VertexBufferLayout& GetVertexBufferLayout() const { return layout; }

protected:
    VertexArray va;
    VertexBuffer vb;
    IndexBuffer ib;
    VertexBufferLayout layout;
};