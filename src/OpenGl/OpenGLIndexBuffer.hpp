#pragma once
#include"EngineApi.hpp"
#include "Graphics/IndexBuffer.hpp"
#include"glad/glad.h"
#include"KnightEnginepch.h"
class OpenGLIndexBuffer : public IndexBuffer
{
public:
	OpenGLIndexBuffer(uint32_t* indices,uint32_t size):m_size(size) {
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	void Bind() const override;
	void Unbind() const override;

	uint32_t GetSize() const override;
	static IndexBuffer*  Create(uint32_t*indices,uint32_t size) {
		return new OpenGLIndexBuffer(indices,size);
	}
private:
	uint32_t m_RendererID;
	uint32_t m_size = 0;
};

