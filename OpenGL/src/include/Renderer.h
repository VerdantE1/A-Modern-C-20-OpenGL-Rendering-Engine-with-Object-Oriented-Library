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

	//ͨ�õ���VertexArray, IndexBuffer��Shader����Ⱦ����������ΪͼԪ����Ⱦ����
	// �ú������Զ���VAO, IBO��Shader��������
	void Draw(const VertexArray& va, const IndexBuffer& ib , const Shader& shader) const;

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