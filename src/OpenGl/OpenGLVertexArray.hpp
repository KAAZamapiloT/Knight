#pragma once
#include "EngineApi.hpp"
#include "Graphics/VertexArray.hpp"
class KNIGHT_ENGINE_API OpenGLVertexArray :public VertexArray
{
public:
	OpenGLVertexArray();
	~OpenGLVertexArray();
	
	void Bind() const override;

	void UnBind() const override;

	void AddVertexBuffer(const VertexBuffer& vertexBuffer) override;

	void SetIndexBuffer(const IndexBuffer& indexBuffer) override;

	const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;

	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;
	static std::shared_ptr<VertexArray> Create() ;

private:

	uint32_t m_RendererID;
	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
};

