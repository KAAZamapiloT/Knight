#pragma once
#include"EngineApi.hpp"
#include "Graphics/IndexBuffer.hpp"
#include"glad/glad.h"
#include <memory>
class OpenGLIndexBuffer : public IndexBuffer
{
public:
	OpenGLIndexBuffer(uint32_t* indices,uint32_t size):m_size(size) {
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(int), indices, GL_STATIC_DRAW);
	}

	void Bind() override;
	void Unbind() override;

	uint32_t GetSize() const;
	static std::shared_ptr<IndexBuffer>  Create(uint32_t*indices,uint32_t size) {
		return std::make_shared<OpenGLIndexBuffer>(indices,size);
	}
private:
	uint32_t m_RendererID;
	uint32_t m_size = 0;
};

