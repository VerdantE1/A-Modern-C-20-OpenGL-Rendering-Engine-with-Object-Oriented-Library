#pragma once
#include "Renderer.h"
/*
* Texture will be assigned in orderly from 0 start. This is force for unifying the bind interface.
*/
class Texture : public Resource
{
private:
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_Bpp;
	inline static unsigned int s_NextAvailabelSlot = 0;
	unsigned int m_AssignedSlot = -1; //This Slot AssignedSlot by Renderer

public:

	Texture(const std::string& filepath);
	~Texture();

	void Bind() const override; 
	void Unbind() const override;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline int GetBpp() const { return m_Bpp; } 
	inline unsigned int GetAssignedSlot() const { return m_AssignedSlot; }


	
};

