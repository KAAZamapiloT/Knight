#include "openGLVertexArray.hpp"
#include "glad/glad.h"


OpenGLVertexArray::OpenGLVertexArray()
	: m_RendererID(0)
{
	// Initialize OpenGL Vertex Array Object (VAO)
	
	glGenVertexArrays(1, &m_RendererID);
	
}

OpenGLVertexArray::~OpenGLVertexArray() {
	glDeleteVertexArrays(1, &m_RendererID);
}
void OpenGLVertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void OpenGLVertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	Bind();
	vertexBuffer->Bind();   // Correct: call through shared_ptr

	// NOTE: you’ll want a real layout system.  For now:
	for (auto& ele : vertexBuffer->GetLayout())
	{
		glEnableVertexAttribArray(ele.GetIndex());
		glVertexAttribPointer(ele.GetIndex(), ele.GetComponentCount(), ShaderDataType(ele.Type),
			(ele.Normalized) ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(), (const void*)ele.Offset);
	}
	

	m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	Bind();
	indexBuffer->Bind();
	m_IndexBuffer = indexBuffer;
}

const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
{
	return m_VertexBuffers;
}

const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
{
	return m_IndexBuffer;
}

