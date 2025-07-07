#include "OpenGLVertexBuffer.hpp"

void OpenGLVertexBuffer::Bind() const 
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

}

void OpenGLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
{
	m_Layout = layout;
	uint32_t offset = 0;
	for (const auto& element : m_Layout.GetElements())
	{
	
		offset += element.Size;
	}
}
