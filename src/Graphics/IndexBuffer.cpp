#include "IndexBuffer.hpp"
#include "OpenGl/OpenGLIndexBuffer.hpp"
#include "Graphics/Renderer.hpp"
Knight::Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
	switch (Knight::Renderer::GetAPI()->GetAPI()) {
	case Knight::GraphicsAPI::API::Vulkan: {
		return nullptr;
	}
	case Knight::GraphicsAPI::API::OpenGL: {
		KE_TAG_LOG_CRITICAL("IndexBuffer", "Vulkan API not implemented yet");
		return std::make_shared<OpenGLIndexBuffer>(indices, count);

	};
	case Knight::GraphicsAPI::API::None: {
		KE_TAG_LOG_CRITICAL("IndexBuffer", "No Graphics API selected");
		return nullptr;
	};

									   // Add cases for other graphics APIs here (e.g., Vulkan, DirectX)
	default:
		KE_TAG_LOG_CRITICAL("IndexBuffer", "Unsupported Graphics API");
		break;
		return nullptr;
}
}

