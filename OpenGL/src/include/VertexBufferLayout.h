#pragma once
#include <memory>
#include <vector>
#include <GL/glew.h>
#include <stdexcept>
#include <type_traits>
#include <variant>
#include <iostream>
/*
* This class is used to define the layout of a vertex buffer.or you could say,it is used to interpret the data in a vertex buffer.
* type and count can describe the size of the data per vertex prop.Nomalized is used to indicate whether the data should be normalized or not.
* 
* 
* A Vertex has many attributes, such as posItion , color , texture coordinates, etc. Each Push of this class represents a single attribute of the vertex.
* So you just need to Push the count of the attribute order is ok.
*/

//a VertexBufferElement is a single element in a vertex buffer layout, which describes the type and size of the data.
struct VertexLayoutElement {
	GLenum type;				// Type of the data (e.g., GL_FLOAT, GL_INT)
	GLint a_count;				// The number of components per generic vertex attribute. !Noting this is attribute a_count, not the whole vertex.
	GLboolean normalized;		// Whether the data should be normalized (e.g., for color values)

	static unsigned int GetSizeOfType(GLenum type)
	{
		switch (type)
		{
			case GL_FLOAT: return sizeof(float);
			case GL_UNSIGNED_INT: return sizeof(unsigned int);
			case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
			default:
				// If the type is not recognized, throw an error or handle it appropriately
				throw std::runtime_error("Unsupported type in VertexBufferElement");
		}
	}
};


class VertexBufferLayout {
public:
	using SupportedTypes = std::variant<float, unsigned int, unsigned char>;

	VertexBufferLayout() : m_Stride(0) {}

	VertexBufferLayout(std::vector<SupportedTypes> acnt_vec)
		: m_Stride(0)
	{
		for (auto& v : acnt_vec)
		{
			//Get 
			visit(
				[this](auto d) {Push(d); }, v
			);

		}
	}
	
	//Only float,int,char will be in Push(T), Other can transform to int,so to this branch;
	void Push(int a_count)
	{
		std::cout << "This type is not support now" << std::endl;
		std::exit(-1);
	}

	//SFINAE (Need C++ 17 or later)
	template<typename T>
	std::enable_if_t<
		std::is_same_v<T,float> ||
		std::is_same_v<T,unsigned int> || 
		std::is_same_v<T,unsigned char>
	>
	Push(T a_count)
	{
		unsigned int gl_type = 0;
		unsigned char normalized = 0;
		if constexpr (std::is_same_v<T,float>){
			gl_type = GL_FLOAT;
			normalized = GL_FALSE;
		}
		else if constexpr (std::is_same_v<T, unsigned int>) {
			gl_type = GL_UNSIGNED_INT;
			normalized = GL_FALSE;
		}
		else if constexpr (std::is_same_v<T, unsigned char>) {
			gl_type = GL_UNSIGNED_BYTE;
			normalized = GL_TRUE;
		}
		else {
			throw std::runtime_error("Unsupported type in VertexBufferLayout::Push");
		}
		m_Elements.push_back({ gl_type,(int)(a_count),normalized });
		m_Stride += a_count * VertexLayoutElement::GetSizeOfType(gl_type);
	}



	inline const std::vector <VertexLayoutElement>& GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
private:
	std::vector<VertexLayoutElement> m_Elements; 
	unsigned int m_Stride;
};
