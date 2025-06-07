#include "OpenGlTexture.hpp"

OpenGlTexture::OpenGlTexture(const char* path)
{
   
}

OpenGlTexture::~OpenGlTexture()
{
}

void OpenGlTexture::Bind(unsigned int slot) const
{
}

void OpenGlTexture::Unbind() const
{
}

unsigned int OpenGlTexture::GetWidth() const
{
	return m_width;
}

unsigned int OpenGlTexture::GetHeight() const
{
	return m_height;
}

unsigned int OpenGlTexture::GetID() const
{
	return m_textureID;
}
