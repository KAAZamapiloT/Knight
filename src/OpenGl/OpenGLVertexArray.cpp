#include "openGLVertexArray.hpp"
#include "glad/glad.h"


OpenGLVertexArray::OpenGLVertexArray()
	: m_RendererID(0)
{
	// Initialize OpenGL Vertex Array Object (VAO)
	auto vao = Create();
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

void OpenGLVertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer)
{
    Bind();  // Bind VAO
	//vertexBuffer.Bind();  // Bind the vertex buffer
    
}

void OpenGLVertexArray::SetIndexBuffer(const IndexBuffer& indexBuffer)
{
}

const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
{
	return m_VertexBuffers;
}

const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
{
	return m_IndexBuffer;
}

std::shared_ptr<VertexArray> OpenGLVertexArray::Create()
{
	return std::make_shared<OpenGLVertexArray>();
}
