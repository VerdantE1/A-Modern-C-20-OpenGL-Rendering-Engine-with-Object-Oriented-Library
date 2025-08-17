#pragma once
#include "Shaper.h"
#include <cmath> 
#include <vector> 
#include <glm/glm.hpp> 
#include <stdexcept>

class Torus : public Shaper
{
private:
	int majorSegments;  // 主环方向的分段数
	int minorSegments;  // 小环方向的分段数
	float majorRadius;  // 主半径（环的中心到管子中心的距离）
	float minorRadius;  // 小半径（管子的半径）
	int numVertices;
	int numIndices;
	std::vector<float> vertexData;
	std::vector<unsigned int> indexData;
	
	void generateVertices(std::vector<float>& vertexData, std::vector<unsigned int>& indexData);

	float toRadians(float angle) const {
		return angle * 3.14159265358979323846f / 180.0f; // π = 3.14159265358979323846
	}

public:
	// majorRadius: 主半径, minorRadius: 小半径, majorSegments: 主环分段, minorSegments: 小环分段
	Torus(float majorRadius = 2.0f, float minorRadius = 0.5f, int majorSegments = 36, int minorSegments = 18)
		: Shaper(nullptr, 0, nullptr, 0, { (float)3, (float)2, (float)3 }), 
		  majorRadius(majorRadius), minorRadius(minorRadius),
		  majorSegments(majorSegments), minorSegments(minorSegments),
		  numVertices(0), numIndices(0)
	{
		generateVertices(vertexData, indexData);
		vb = std::move(VertexBuffer(vertexData));
		ib = std::move(IndexBuffer(indexData));
		// layout已经初始化过
		va.LinkBufferAndLayout(vb, layout);
	}

	int getNumVertices() const { return numVertices; }
	int getNumIndices() const { return numIndices; }
	float getMajorRadius() const { return majorRadius; }
	float getMinorRadius() const { return minorRadius; }

	void Draw(Shader& shader, const Renderer& renderer) override {
		throw std::logic_error("Draw() not implemented for this subclass!");
	}
};

inline void Torus::generateVertices(std::vector<float>& vertexData, std::vector<unsigned int>& indexData)
{
	numVertices = (majorSegments + 1) * (minorSegments + 1);
	numIndices = majorSegments * minorSegments * 6;  // 每个面两个三角形，每个三角形三个顶点

	vertexData.resize(numVertices * 8); // 3(位置) + 2(纹理) + 3(法向量) = 8

	// 生成顶点数据
	for (int i = 0; i <= majorSegments; i++) {
		for (int j = 0; j <= minorSegments; j++) {
			// 计算角度
			float u = (float)i / majorSegments * 360.0f;  // 主环角度 (0-360度)
			float v = (float)j / minorSegments * 360.0f;  // 小环角度 (0-360度)
			
			float uRad = toRadians(u);
			float vRad = toRadians(v);

			// 计算顶点位置
			float x = (majorRadius + minorRadius * cos(vRad)) * cos(uRad);
			float y = minorRadius * sin(vRad);
			float z = (majorRadius + minorRadius * cos(vRad)) * sin(uRad);

			// 计算法向量
			float nx = cos(vRad) * cos(uRad);
			float ny = sin(vRad);
			float nz = cos(vRad) * sin(uRad);

			// 计算数组索引
			int idx = (i * (minorSegments + 1) + j) * 8;

			// 存储位置坐标
			vertexData[idx + 0] = x;
			vertexData[idx + 1] = y;
			vertexData[idx + 2] = z;

			// 存储纹理坐标
			vertexData[idx + 3] = (float)i / majorSegments;  // u坐标
			vertexData[idx + 4] = (float)j / minorSegments;  // v坐标

			// 存储法向量
			vertexData[idx + 5] = nx;
			vertexData[idx + 6] = ny;
			vertexData[idx + 7] = nz;
		}
	}

	// 生成索引数据
	indexData.resize(numIndices);
	
	for (int i = 0; i < majorSegments; i++) {
		for (int j = 0; j < minorSegments; j++) {
			// 计算四个顶点的索引
			int current = i * (minorSegments + 1) + j;
			int next = current + minorSegments + 1;
			
			int base = 6 * (i * minorSegments + j);
			
			// 第一个三角形
			indexData[base + 0] = current;
			indexData[base + 1] = next;
			indexData[base + 2] = current + 1;
			
			// 第二个三角形
			indexData[base + 3] = current + 1;
			indexData[base + 4] = next;
			indexData[base + 5] = next + 1;
		}
	}
}

