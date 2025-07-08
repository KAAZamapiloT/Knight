#include "VertexArray.hpp"
#include"Graphics/Renderer.hpp"
#include"OpenGl/OpenGLVertexArray.hpp"
VertexArray* VertexArray::Create()
{
	switch (Knight::Renderer::GetAPI()->GetAPI()) {
	case Knight::GraphicsAPI::API::OpenGL: {
		return new OpenGLVertexArray();
	}
	case Knight::GraphicsAPI::API::Vulkan: {
		KE_TAG_LOG_CRITICAL("VertexBuffer", "Vulkan API not implemented yet");
		return nullptr;

	};
	case Knight::GraphicsAPI::API::None: {
		KE_TAG_LOG_CRITICAL("VertexBuffer", "No Graphics API selected");
		return nullptr;
	};

									   // Add cases for other graphics APIs here (e.g., Vulkan, DirectX)
	default:
		KE_TAG_LOG_CRITICAL("VertexBuffer", "Unsupported Graphics API");
		break;
		return nullptr;
	}
}

