#include"shaderComp.h"
#include"Graphics/Renderer.hpp"
#include"OpenGl/OpenGLShaderComp.hpp"

Knight::Ref<KnightEngine::ShaderComp> KnightEngine::ShaderComp::Create(const std::string& name,const std::string& VertexSource, const std::string& FragmentSource)
{
	switch (Knight::Renderer::GetAPI()->GetAPI()) {
	case Knight::GraphicsAPI::API::OpenGL: {
		return  std::make_shared<OpenGLShaderComp>(name, VertexSource, FragmentSource);
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

Knight::Ref<KnightEngine::ShaderComp> KnightEngine::ShaderComp::Create(const std::string& filepath)
{
	switch (Knight::Renderer::GetAPI()->GetAPI()) {
	case Knight::GraphicsAPI::API::OpenGL: {
		return std::make_shared<OpenGLShaderComp>(filepath);
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

void KnightEngine::ShaderLibray::Add(const std::string& name, Knight::Ref<ShaderComp>& S)
{
	KE_CORE_ASSERT(m_ShaderMap.find(name) == m_ShaderMap.end(), "SHADER OF SAME NAME ALREADY EXSISTS");
	m_ShaderMap[name] = S;
}

void KnightEngine::ShaderLibray::Add(const Knight::Ref<ShaderComp>& S)
{
	auto& name=S->GetName();
	KE_CORE_ASSERT(m_ShaderMap.find(name) == m_ShaderMap.end(), "SHADER OF SAME NAME ALREADY EXSISTS");
	m_ShaderMap[name]=S;
}

Knight::Ref<KnightEngine::ShaderComp> KnightEngine::ShaderLibray::Load(const std::string filepath)
{
	auto Shader = ShaderComp::Create(filepath);
	Add(Shader);
	return Shader;
}

Knight::Ref<KnightEngine::ShaderComp> KnightEngine::ShaderLibray::Load(const std::string name, const std::string filepath)
{
	auto Shader = ShaderComp::Create(filepath);
	Add(name,Shader);
	return Shader;
}

Knight::Ref<KnightEngine::ShaderComp> KnightEngine::ShaderLibray::Get(const std::string& name)
{
	if (!Exists(name)) {
		// Log a warning or error instead of asserting
		KE_TAG_LOG_CRITICAL("SHADER LIBRARY :GET", "Shader '{}' not found in library.", name.c_str());
		return nullptr;
	}
	return m_ShaderMap[name];
}
