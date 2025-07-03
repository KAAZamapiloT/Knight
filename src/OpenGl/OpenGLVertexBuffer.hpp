#pragma once
#include"EngineApi.hpp"
#include"Graphics/VertexBuffer.hpp"
#include"KnightEnginepch.h"
#include"glad/glad.h"
class KNIGHT_ENGINE_API OpenGLVertexBuffer :public VertexBuffer
{
public:
	OpenGLVertexBuffer(float* data, uint32_t size) {
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void Bind() const override;
	void Unbind() const  override;
	static std::shared_ptr<VertexBuffer> Create(float* data, uint32_t size) {
		return std::make_shared<OpenGLVertexBuffer>(data, size);
	}
private:
	uint32_t m_RendererID;
	uint32_t m_Size = 0;
};

