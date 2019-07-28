#include "Texture.h"
#include "Renderer.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& filepath)
	: m_Renderer(0), m_FilePath(filepath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);     //flip the texture to read bytes in from the bottom to top
	m_LocalBuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	if (m_LocalBuffer)
		std::cout << "Texture image is loaded." << std::endl;
	else
		std::cout << "Failed to load texture image." << std::endl;
	GLCall(glGenTextures(1, &m_Renderer));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_Renderer));
	GLCall(glTextureParameteri(m_Renderer, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTextureParameteri(m_Renderer, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));               //Unbind the texture 
	stbi_image_free(m_LocalBuffer);                        //free the CPU side locabuffer memory
	std::cout << "Texture image CPU side local buffer has been freed." << std::endl;
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_Renderer));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_Renderer));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
