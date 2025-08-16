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

	//ͨ�õ���VertexArray, IndexBuffer��Shader����Ⱦ����������ΪͼԪ����Ⱦ����
	// �ú������Զ���VAO, IBO��Shader��������
	void Draw(const VertexArray& va, const IndexBuffer& ib , const Shader& shader) const;
	void Draw(const Shaper& sp, const Shader& shader) const;
	void Draw(const Shaper& sp, const Shader& shader, const Texture& texture) const; // �ú������Զ���VAO, IBO��Shader��������Ⱦǰ������

	void DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int instanceCount) const; //���û�ȷ��shader����instance��Ҫ��
	void ClearColor();

	// �Ƿ�ʹ���߿�ģʽ����Ȳ��ԣ��ɶ�д��
	mutable bool UsePolygonMode = false;
	mutable bool UseDepthTest = false;
	mutable bool UseCullFace = false;

	// �����߿�ģʽ��mode=trueΪ�߿�falseΪ��䣩
	const Renderer& SetPolygonMode(bool mode) const;

	// �����Ƿ�����Ȳ���
	const Renderer& SetDepthTest(bool enable) const;

	// �����޳��棨enable=true������front��back�ֱ��ʾ�Ƿ��޳�ǰ��ͺ��棩
	const Renderer& SetCullFace(bool enable ,bool front=false, bool back = true) const;
private:
};