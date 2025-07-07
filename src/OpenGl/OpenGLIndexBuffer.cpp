#include "OpenGLIndexBuffer.hpp"

void OpenGLIndexBuffer::Bind() const 
{
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void OpenGLIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t OpenGLIndexBuffer::GetSize() const
{
	return m_size;
}

