#include"shaderComp.h"
#include"Graphics/Renderer.hpp"
#include"OpenGl/OpenGLShaderComp.hpp"

KnightEngine::ShaderComp* KnightEngine::ShaderComp::Create(const std::string& VertexSource, const std::string& FragmentSource)
{
	switch (Knight::Renderer::GetAPI()->GetAPI()) {
	case Knight::GraphicsAPI::API::OpenGL: {
		return new OpenGLShaderComp(VertexSource,FragmentSource);
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

KnightEngine::ShaderComp* KnightEngine::ShaderComp::Create(const std::string& filepath)
{
	switch (Knight::Renderer::GetAPI()->GetAPI()) {
	case Knight::GraphicsAPI::API::OpenGL: {
		return new OpenGLShaderComp(filepath);
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
