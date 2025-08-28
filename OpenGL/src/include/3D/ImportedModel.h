#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include "Shaper.h"

/*
1.Only Support Obj format.
2.Only Suport 3 properties: position, texture coordinate, normal. (Should be current existing in the model)
3.Only Support Triangles.
4.Only Support space separated.
5.No process for concrect texture.
6.Fully Unfold: For simple , we don't use index method to organize the vertex data. We creat 3 vertices for each triangle though it can cause some redundancy.
*/
class ImportedModel :public Shaper
{
public:
	int numVertices;
	std::vector<float> vertexData;  // 交错存储: pos(3) + texCoord(2) + normal(3) = 8 floats per vertex

	std::vector<float> positionData;    // 3 floats per vertex (临时存储原始数据)
	std::vector<float> textureCoordData; // 2 floats per vertex (临时存储原始数据)
	std::vector<float> normalData;      // 3 floats per vertex (临时存储原始数据)

	ImportedModel() = delete; // 禁止默认构造函数
	ImportedModel(const std::string& filePath);
	void parseOBJ(const std::string& filePath);

	void Draw(Shader& shader, const Renderer& renderer) override {
		throw std::logic_error("Draw() not implemented for ImportedModel!");
	}


	int getNumVertices() const { return numVertices; }
	const std::vector<float>& getVertexData() const { return vertexData; }
	const std::vector<float>& getPositionData() const { return positionData; }
	const std::vector<float>& getTextureCoordData() const { return textureCoordData; }
	const std::vector<float>& getNormalData() const { return normalData; }

};

inline ImportedModel::ImportedModel(const std::string& filePath)
	: Shaper(nullptr, 0, nullptr, 0, { (float)3, (float)2, (float)3 }), numVertices(0)
{
	parseOBJ(filePath);
	vb = std::move(VertexBuffer(vertexData));
	va.LinkBufferAndLayout(vb, layout);


#ifdef IMPORTED_MODEL_DEBUG

	// 添加调试信息
	std::cout << "ImportedModel loaded:" << std::endl;
	std::cout << "  Vertices: " << numVertices << std::endl;
	std::cout << "  Vertex data size: " << vertexData.size() << std::endl;
	std::cout << "  Expected size: " << numVertices * 8 << std::endl;

#endif
}

inline void ImportedModel::parseOBJ(const std::string& filePath)
{
	using namespace std;
	std::ifstream ifs(filePath, ios::in);
	if (!ifs.is_open())
	{
		throw std::runtime_error("Failed to open file: " + filePath);
	}
	string line="";

	while (getline(ifs, line)) {
		if (line.empty() || line[0] == '#') {
			continue; // Skip empty lines and comments
		}

		istringstream iss(line);
		string prefix;
		iss >> prefix;

		if (prefix == "v")
		{
			float x, y, z;
			iss >> x >> y >> z;
			positionData.push_back(x);
			positionData.push_back(y);
			positionData.push_back(z);
			
			iss >> std::ws;
			assert(iss.eof()); // 确保行末没有额外数据
			

		}
		else if(prefix == "vt")
		{
			float u, v;
			iss >> u >> v;
			textureCoordData.push_back(u);
			textureCoordData.push_back(v);

			iss >> std::ws;
			assert(iss.eof()); // 确保行末没有额外数据
		}
		else if (prefix == "vn")
		{
			float nx, ny, nz;
			iss >> nx >> ny >> nz;
			normalData.push_back(nx);
			normalData.push_back(ny);
			normalData.push_back(nz);

			iss >> std::ws;
			assert(iss.eof()); // 确保行末没有额外数据
		}
		else if (prefix == "f")
		{
			int posIndex[3], texIndex[3], normIndex[3];
			char slash; // 用于跳过斜杠
			for (int i = 0; i < 3; ++i) {
				iss >> posIndex[i] >> slash >> texIndex[i] >> slash >> normIndex[i];
				posIndex[i]--; // OBJ索引从1开始，C++从0开始
				texIndex[i]--;
				normIndex[i]--;
				
				vertexData.push_back(positionData[posIndex[i] * 3]);
				vertexData.push_back(positionData[posIndex[i] * 3 + 1]);
				vertexData.push_back(positionData[posIndex[i] * 3 + 2]);
				vertexData.push_back(textureCoordData[texIndex[i] * 2]);
				vertexData.push_back(textureCoordData[texIndex[i] * 2 + 1]);
				vertexData.push_back(normalData[normIndex[i] * 3]);
				vertexData.push_back(normalData[normIndex[i] * 3 + 1]);
				vertexData.push_back(normalData[normIndex[i] * 3 + 2]);
			}
			numVertices += 3; // 每个面有三个顶点

			iss >> std::ws;
			assert(iss.eof()); // 确保行末没有额外数据
		}
	}
		




}