#pragma once
#include "Shaper.h"
#include <cmath> 
#include <vector> 
#include <glm/glm.hpp> 
#include <stdexcept>

class Sphere : public Shaper
{
private:
	int numSegment;
	int numVertices;
	int numIndices;
	std::vector<float> vertexData;
	std::vector<unsigned int> indexData;
	void generateVertices(std::vector<float>& vertexData, std::vector<unsigned int>& indexDate);

	float toRadians(float angle) const {
		return angle * 3.14159265358979323846f / 180.0f; // π = 3.14159265358979323846
	}

public:
	//numSegement是切片数量
	Sphere(int numSegment = 36)
		: Shaper(nullptr, 0, nullptr, 0, { (float)3, (float)2, (float)3 }), numVertices(0), numIndices(0), numSegment(numSegment)
	{

		generateVertices(vertexData,indexData);
		vb = std::move(VertexBuffer(vertexData));
		ib = std::move(IndexBuffer(indexData));
		//layout已经初始化过
		va.LinkBufferAndLayout(vb, layout);



	}

	int getNumVertices() const { return numVertices; }
	int getNumIndices() const { return numIndices; }

	void Draw(Shader& shader, const Renderer& renderer) override {
		throw std::logic_error(" Draw() not implemented for this subclass!");
	}

};


inline void Sphere::generateVertices(std::vector<float>& vertexData, std::vector<unsigned int>& indexDate)
{
	numVertices = (numSegment + 1) * (numSegment  + 1);	//多一个顶点缝合纹理
	numIndices = numSegment * numSegment * 6;				// 每个面两个三角形，每个三角形三个顶点

	vertexData.resize(numVertices * 8); // 3+2+3=8,

	//计算顶点位置、纹理坐标和法向量
	for (int i = 0; i <= numSegment; i++) {
		for (int j = 0; j <= numSegment; j++) {
			float y = (float)cos(toRadians(180.0f - i * 180.0f / numSegment));
			float x = -(float)cos(toRadians(j * 360.0f / numSegment)) * (float)abs(cos(asin(y)));
			float z = (float)sin(toRadians(j * 360.0f / numSegment)) * (float)abs(cos(asin(y)));

			// Calculate indices for flat array
			int idx = (i * (numSegment + 1) + j) * 8;

			// Position
			vertexData[idx + 0] = x;
			vertexData[idx + 1] = y;
			vertexData[idx + 2] = z;

			// TexCoords
			vertexData[idx + 3] = (float)j / numSegment;
			vertexData[idx + 4] = (float)i / numSegment;

			// Normal
			vertexData[idx + 5] = x;
			vertexData[idx + 6] = y;
			vertexData[idx + 7] = z;
		}
	}

	indexDate.resize(numIndices);

	for (int i = 0; i < numSegment; i++) {
		for (int j = 0; j < numSegment; j++) {
			int base = 6 * (i * numSegment + j);
			int row1 = i * (numSegment + 1);
			int row2 = (i + 1) * (numSegment + 1);

			indexDate[base + 0] = row1 + j;
			indexDate[base + 1] = row1 + j + 1;
			indexDate[base + 2] = row2 + j;
			indexDate[base + 3] = row1 + j + 1;
			indexDate[base + 4] = row2 + j + 1;
			indexDate[base + 5] = row2 + j;
		}
	}
}
/*
 * Copyright (c) 2025 
 * Email: 2523877046@qq.com
 * Author: Baiqiang Long (Buzzlight)
 * 
 * This file is part of the ReduxGL project.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
