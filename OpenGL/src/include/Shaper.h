#pragma once
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <Shader.h>
#include <Renderer.h>

class Shaper {
public:
    virtual ~Shaper() = default;
    virtual void Draw(Shader& shader,Renderer& renderer) = 0;
    VertexArray& GetVertexArray() { return va; }
protected:
    VertexArray va;
};