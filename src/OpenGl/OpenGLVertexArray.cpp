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
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);

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

