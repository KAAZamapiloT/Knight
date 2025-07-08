#pragma once
#include "EngineApi.hpp"
#include"Graphics/VertexArray.hpp"
#include"Graphics/BufferLayout.hpp"
#include"OpenGl/OpenGLVertexBuffer.hpp"
#include"OpenGl/OpenGLIndexBuffer.hpp"
#include "KnightEnginepch.h"
class KNIGHT_ENGINE_API OpenGLVertexArray :public VertexArray
{
public:
	OpenGLVertexArray();
	~OpenGLVertexArray();
	
	void Bind() const override;

	void UnBind() const override;

	

	const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;

	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;

	virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
	virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
	
	void SetLayout(BufferLayout&Layout) override;

//	static VertexArray* Create() {
//		return new OpenGLVertexArray();
//	}

private:

	uint32_t m_RendererID;
	std::vector<std::shared_ptr<VertexBuffer>> M_VertexBuffers;
	std::shared_ptr<IndexBuffer> M_IndexBuffer;
};

