#include "Texture.h"
#include "vendor/stb_image/stb_image.h"


Texture::Texture(const std::string& filepath)
	:m_FilePath(filepath),m_LocalBuffer(nullptr),m_Width(0),m_Height(0),m_Bpp(0),m_AssignedSlot(s_NextAvailabelSlot++)
{
	stbi_set_flip_vertically_on_load(1); //OpenGL wants texture pixels to be left bottom,so flip it
	m_LocalBuffer = stbi_load(filepath.c_str(),&m_Width,&m_Height,&m_Bpp,4);
	
	GLCall(glGenTextures(1, &m_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
	
	//When Magnify and Minify Zones
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

	//When Wrapping
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	
	//Ram to VRam
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
}


Texture::~Texture()
{
	--s_NextAvailabelSlot;
	GLCall(glDeleteTextures(1, &m_id));
}

void Texture::Bind() const
{
	if (m_AssignedSlot == -1)
	{
		std::cerr << "Texture Bind error: This Texture instance is not assigend yet for some unkown reason ! " << std::endl;
	}
	GLCall(glActiveTexture(GL_TEXTURE0 + m_AssignedSlot))
	GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

