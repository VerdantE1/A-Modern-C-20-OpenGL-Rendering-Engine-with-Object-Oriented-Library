#include "Renderer.h"
#include "Utility.h"
#include "IndexBuffer.h"

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::ClearColor()
{
	GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f)); // 比如设置一个深绿色背景
}

const Renderer& Renderer::SetPolygonMode(bool mode) const
{
	if (mode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 线框
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 填充
	return (*this);
}

const Renderer& Renderer::SetDepthTest(bool enable) const
{
	if (enable)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	return (*this);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	BindAll(va, ib, shader);
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, (void*)0)); 

}

void Renderer::DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int instanceCount) const
{
	BindAll(va,ib,shader);
	GLCall(glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, (void*)0, instanceCount));
}


