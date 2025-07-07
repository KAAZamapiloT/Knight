#pragma once
#include "EngineApi.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"       
#include "Graphics/IndexBuffer.hpp"  
#include "KnightEnginepch.h"
class KNIGHT_ENGINE_API OpenGLVertexArray :public VertexArray
{
public:
	OpenGLVertexArray();
	~OpenGLVertexArray();
	
	void Bind() const override;

	void UnBind() const override;

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;

	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

	const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;

	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;

	static VertexArray* Create() {
		return new OpenGLVertexArray();
	}

private:

	uint32_t m_RendererID;
	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
};

