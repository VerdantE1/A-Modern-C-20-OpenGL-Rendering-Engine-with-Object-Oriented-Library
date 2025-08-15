#include "Shaper.h"
#include "Renderer.h"

class Pyramid :public Shaper
{
	inline static constexpr float vertices[] = {
		// 顶点位置
		 0.0f,  1.0f, 0.0f,   // 顶点
		-1.0f, -1.0f, 1.0f,   // 底面左前
		 1.0f, -1.0f, 1.0f,   // 底面右前
		 1.0f, -1.0f, -1.0f,  // 底面右后
		-1.0f, -1.0f, -1.0f,  // 底面左后
	};
	inline static constexpr unsigned int indices[] = {
		1, 2, 3,	// 底面
		3, 4, 1,
		0, 1, 2,	// 前面
		0, 2, 3,	// 右面
		0, 3, 4, 	// 后面
		0, 4, 1		// 左面
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