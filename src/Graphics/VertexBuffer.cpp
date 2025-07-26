#include "VertexBuffer.hpp"
#include"Graphics/Renderer.hpp"
#include"Core/Core.h"
#include"OpenGl/OpenGLVertexBuffer.hpp"

	Knight::Ref<VertexBuffer> VertexBuffer::Create(float* data, uint32_t size)
	{
		switch (Knight::Renderer::GetAPI()->GetAPI()) {
		case Knight::GraphicsAPI::API::Vulkan: {
			return nullptr;
		}
		case Knight::GraphicsAPI::API::OpenGL: {
			KE_TAG_LOG_CRITICAL("VertexBuffer", "Vulkan API not implemented yet");
			return std::make_shared<OpenGLVertexBuffer>(data,size);

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
