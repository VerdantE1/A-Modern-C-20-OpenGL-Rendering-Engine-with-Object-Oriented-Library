#pragma once

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer
{
public:

	void Clear() const;

	//ͨ�õ���VertexArray, IndexBuffer��Shader����Ⱦ����������ΪͼԪ����Ⱦ����
	// �ú������Զ���VAO, IBO��Shader��������
	void Draw(const VertexArray& va, const IndexBuffer& ib , const Shader& shader) const;
	//void Draw(const Shaper& sp, const Shader& shader) const;

	void DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int instanceCount) const; //���û�ȷ��shader����instance��Ҫ��
	void ClearColor();

	// �Ƿ�ʹ���߿�ģʽ����Ȳ��ԣ��ɶ�д��
	mutable bool UsePolygonMode = false;
	mutable bool UseDepthTest = false;

	// �����߿�ģʽ��mode=trueΪ�߿�falseΪ��䣩
	const Renderer& SetPolygonMode(bool mode) const;

	// �����Ƿ�����Ȳ���
	const Renderer& SetDepthTest(bool enable) const;
private:
};