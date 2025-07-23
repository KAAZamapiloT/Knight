#include "VertexArray.hpp"
#include"Graphics/Renderer.hpp"
#include"OpenGl/OpenGLVertexArray.hpp"

Knight::Ref<VertexArray> VertexArray::Create()
{
	switch (Knight::Renderer::GetAPI()->GetAPI()) {
	case Knight::GraphicsAPI::API::OpenGL: {
		return std::make_shared<OpenGLVertexArray>();
	}
	case Knight::GraphicsAPI::API::Vulkan: {
		KE_TAG_LOG_CRITICAL("VertexArray", "Vulkan API not implemented yet");
		return nullptr;

	};
	case Knight::GraphicsAPI::API::None: {
		KE_TAG_LOG_CRITICAL("VertexArray", "No Graphics API selected");
		return nullptr;
	};

									   // Add cases for other graphics APIs here (e.g., Vulkan, DirectX)
	default:
		KE_TAG_LOG_CRITICAL("VertexArray", "Unsupported Graphics API");
		break;
		return nullptr;
	}
}

