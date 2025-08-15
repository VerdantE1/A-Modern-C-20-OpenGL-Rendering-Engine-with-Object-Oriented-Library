#include "Shaper.h"
#include "Renderer.h"

class Pyramid :public Shaper
{
	inline static constexpr float vertices[] = {
		// ����λ��
		 0.0f,  1.0f, 0.0f,   // ����
		-1.0f, -1.0f, 1.0f,   // ������ǰ
		 1.0f, -1.0f, 1.0f,   // ������ǰ
		 1.0f, -1.0f, -1.0f,  // �����Һ�
		-1.0f, -1.0f, -1.0f,  // �������
	};
	inline static constexpr unsigned int indices[] = {
		1, 2, 3,	// ����
		3, 4, 1,
		0, 1, 2,	// ǰ��
		0, 2, 3,	// ����
		0, 3, 4, 	// ����
		0, 4, 1		// ����
	};

public:
	Pyramid() :
		Shaper(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(unsigned int), { (float)3 })
	{
		va.LinkBufferAndLayout(vb, layout);
	}

	void Draw(Shader& shader, const Renderer& renderer) override {
		renderer.Draw(va, ib, shader);
	}
private:

};