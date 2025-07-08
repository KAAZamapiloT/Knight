#include "openGLVertexArray.hpp"
#include "glad/glad.h"
#include"KnightEnginepch.h"
static GLenum ShaderDataType(EDataType E) {
	switch (E) {
	case EDataType::Float:
	case EDataType::Float2:
	case EDataType::Float3:
	case EDataType::Float4:
		return GL_FLOAT;
	case EDataType::Int:
	case EDataType::Int2:
	case EDataType::Int3:
	case EDataType::Int4:
		return GL_INT;
	case EDataType::UInt:
		return GL_UNSIGNED_INT;
	case EDataType::Bool:
		return GL_BOOL;
	case EDataType::Mat2:
	case EDataType::Mat3:
	case EDataType::Mat4:
		return GL_FLOAT;
	default:
		return GL_FLOAT;
	}
}
OpenGLVertexArray::OpenGLVertexArray()
	: m_RendererID(0)
{
	// Initialize OpenGL Vertex Array Object (VAO)
	
	glCreateVertexArrays(1, &m_RendererID);
	//glBindVertexArray(m_RendererID);
	
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


const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
{
	return M_VertexBuffers;
}

const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
{
	return M_IndexBuffer;
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	if (vertexBuffer==nullptr) {
		KE_TAG_LOG_CRITICAL("OpenGLVertexArray:AddVertexBuffer","VERTEX BUFFER IS NULLPTR");
		return;
	}
	Bind();
	vertexBuffer->Bind();
	uint32_t index = 0;
	for (auto& ele : vertexBuffer->GetLayout())
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, ele.GetComponentCount(), ShaderDataType(ele.Type),
			(ele.Normalized) ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(), (const void*)(uintptr_t)ele.Offset);

		KE_TAG_LOG_INFO("VertexArray", "Setting attribute {} with {} components at offset {}",
			index, ele.GetComponentCount(), ele.Offset);
		index++;
	}
	M_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	Bind();
	indexBuffer->Bind();
	M_IndexBuffer = indexBuffer;
	;
}

void OpenGLVertexArray::SetLayout(BufferLayout& Layout)
{
}

