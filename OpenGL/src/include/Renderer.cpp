#include "Renderer.h"


void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::ClearColor()
{
	GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f)); // 比如设置一个深绿色背景
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	BindAll(va, ib, shader);
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, (void*)0)); 

}


