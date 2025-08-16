#pragma once
#include <Texture.h>

class VertexArray;
class IndexBuffer;
class Shader;
class Shaper;

class Renderer
{
public:

	void Clear() const;

	//通用的以VertexArray, IndexBuffer和Shader的渲染并以三角形为图元的渲染函数
	// 该函数会自动绑定VAO, IBO和Shader，并在渲
	void Draw(const VertexArray& va, const IndexBuffer& ib , const Shader& shader) const;
	void Draw(const Shaper& sp, const Shader& shader) const;
	void Draw(const Shaper& sp, const Shader& shader, const Texture& texture) const; // 该函数会自动绑定VAO, IBO和Shader，并在渲染前绑定纹理

	void DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int instanceCount) const; //由用户确保shader符合instance的要求
	void ClearColor();

	// 是否使用线框模式和深度测试（可读写）
	mutable bool UsePolygonMode = false;
	mutable bool UseDepthTest = false;
	mutable bool UseCullFace = false;

	// 设置线框模式（mode=true为线框，false为填充）
	const Renderer& SetPolygonMode(bool mode) const;

	// 设置是否开启深度测试
	const Renderer& SetDepthTest(bool enable) const;

	// 设置剔除面（enable=true开启，front和back分别表示是否剔除前面和后面）
	const Renderer& SetCullFace(bool enable ,bool front=false, bool back = true) const;
private:
};