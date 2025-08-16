#pragma once
#include "Shaper.h"
#include "Renderer.h"
class Cube :public Shaper {
	inline static constexpr float vertices[] = {
		// 位置坐标              // 纹理坐标
		// 前面
		-1.0f, -1.0f,  1.0f,    0.0f, 0.0f,  // 左下
		 1.0f, -1.0f,  1.0f,    1.0f, 0.0f,  // 右下
		 1.0f,  1.0f,  1.0f,    1.0f, 1.0f,  // 右上
		-1.0f,  1.0f,  1.0f,    0.0f, 1.0f,  // 左上
		// 后面
		-1.0f, -1.0f, -1.0f,    1.0f, 0.0f,  // 右下
		 1.0f, -1.0f, -1.0f,    0.0f, 0.0f,  // 左下
		 1.0f,  1.0f, -1.0f,    0.0f, 1.0f,  // 左上
		-1.0f,  1.0f, -1.0f,    1.0f, 1.0f,  // 右上
	};
	inline static constexpr unsigned int indices[] = {
		// 前面
		0, 1, 2, 2, 3, 0,
		// 右面
		1, 5, 6, 6, 2, 1,
		// 后面
		5, 4, 7, 7, 6, 5,
		// 左面
		4, 0, 3, 3, 7, 4,
		// 上面
		3, 2, 6, 6, 7, 3,
		// 下面
		4, 5, 1, 1, 0, 4
	};




public:
	Cube():
		Shaper(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(unsigned int), {(float)3, (float)2})
	{
		va.LinkBufferAndLayout(vb, layout);
	}

	void Draw(Shader& shader, const Renderer& renderer) override {
		renderer.Draw(va, ib, shader);
	}
};