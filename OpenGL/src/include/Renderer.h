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

	//通用的以VertexArray, IndexBuffer和Shader的渲染并以三角形为图元的渲染函数
	// 该函数会自动绑定VAO, IBO和Shader，并在渲
	void Draw(const VertexArray& va, const IndexBuffer& ib , const Shader& shader) const;

	void ClearColor();

	// 是否使用线框模式和深度测试（可读写）
	mutable bool UsePolygonMode = false;
	mutable bool UseDepthTest = false;

	// 设置线框模式（mode=true为线框，false为填充）
	const Renderer& SetPolygonMode(bool mode) const;

	// 设置是否开启深度测试
	const Renderer& SetDepthTest(bool enable) const;
private:
};