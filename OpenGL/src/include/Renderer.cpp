#include "Renderer.h"
#include "Utility.h"
#include "IndexBuffer.h"
#include "Shaper.h"

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

const Renderer& Renderer::SetCullFace(bool enable, bool front, bool back) const
{
	if (enable)
	{
		glEnable(GL_CULL_FACE);
		if (front && back)
			glCullFace(GL_FRONT_AND_BACK); // 启用双面剔除
		else if (front)
			glCullFace(GL_FRONT); // 只剔除前面
		else if (back)
			glCullFace(GL_BACK); // 只剔除后面
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}
	return (*this);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	BindAll(va, ib, shader);
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, (void*)0)); 

}

void Renderer::Draw(const Shaper& sp, const Shader& shader) const
{
	Draw(sp.GetVertexArray(), sp.GetIndexBuffer(), shader);
}

void Renderer::DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int instanceCount) const
{
	BindAll(va,ib,shader);
	GLCall(glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, (void*)0, instanceCount));
}


