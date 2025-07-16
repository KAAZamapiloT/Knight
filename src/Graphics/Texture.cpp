#include "Texture.hpp"
#include"Graphics/Renderer.hpp"
#include"OpenGl/OpenGLTexture.hpp"
#include"memory"
Knight::Ref<Knight::Texture2D> Knight::Texture2D::Create(const std::string& filepath)
{
	switch (Knight::Renderer::GetAPI()->GetAPI()) {
	case Knight::GraphicsAPI::API::OpenGL: {
		return  std::make_shared<Knight::OpenGLTexture2D>(filepath);
	}
	case Knight::GraphicsAPI::API::Vulkan: {
		KE_TAG_LOG_CRITICAL("Texture", "Vulkan API not implemented yet");
		return nullptr;

	};
	case Knight::GraphicsAPI::API::None: {
		KE_TAG_LOG_CRITICAL("Texture", "No Graphics API selected");
		return nullptr;
	};

									   // Add cases for other graphics APIs here (e.g., Vulkan, DirectX)
	default:
		KE_TAG_LOG_CRITICAL("Texture", "Unsupported Graphics API");
		break;
		return nullptr;
	}
}
