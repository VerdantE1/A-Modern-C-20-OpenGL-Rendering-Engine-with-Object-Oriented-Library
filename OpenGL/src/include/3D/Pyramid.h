#include "Shaper.h"
#include "Renderer.h"

class Pyramid :public Shaper
{
	inline static constexpr float vertices[] = {
		// ����λ��                // ��������
		// ע��: Ϊÿ�������ε�ÿ�����㵥��������������
		
		// ����(�������в���)
		 0.0f,  1.0f, 0.0f,      0.5f, 0.0f,   // ���� (����0)
		
		// ���涥�� - ÿ�������в�ͬ���������꣬�ʺϵ���ӳ��
		-1.0f, -1.0f, 1.0f,      0.0f, 0.0f,   // ������ǰ (����1)
		 1.0f, -1.0f, 1.0f,      1.0f, 0.0f,   // ������ǰ (����2)
		 1.0f, -1.0f, -1.0f,     1.0f, 1.0f,   // �����Һ� (����3)
		-1.0f, -1.0f, -1.0f,     0.0f, 1.0f,   // ������� (����4)
		
		// ���涥�� - ÿ������ĵױ߶���ʹ�ò�ͬ����������
		// ǰ��
		-1.0f, -1.0f, 1.0f,      0.0f, 1.0f,   // ǰ������ (����5)
		 1.0f, -1.0f, 1.0f,      1.0f, 1.0f,   // ǰ������ (����6)
		
		// ����
		 1.0f, -1.0f, 1.0f,      0.0f, 1.0f,   // �������� (����7)
		 1.0f, -1.0f, -1.0f,     1.0f, 1.0f,   // �������� (����8)
		
		// ����
		 1.0f, -1.0f, -1.0f,     0.0f, 1.0f,   // �������� (����9)
		-1.0f, -1.0f, -1.0f,     1.0f, 1.0f,   // �������� (����10)
		
		// ����
		-1.0f, -1.0f, -1.0f,     0.0f, 1.0f,   // �������� (����11)
		-1.0f, -1.0f, 1.0f,      1.0f, 1.0f,   // �������� (����12)
	};
	
	// ʹ���µ���������Ӧ�ڶ��������е�λ��
	inline static constexpr unsigned int indices[] = {
		1, 2, 3,	// ����������1
		3, 4, 1,    // ����������2
		0, 5, 6,	// ǰ��
		0, 7, 8,	// ����
		0, 9, 10, 	// ����
		0, 11, 12	// ����
	};

public:
	Pyramid() :
		Shaper(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(unsigned int), { (float)3, (float)2 })
	{
		va.LinkBufferAndLayout(vb, layout);
	}

	void Draw(Shader& shader, const Renderer& renderer) override {
		renderer.Draw(va, ib, shader);
	}
};