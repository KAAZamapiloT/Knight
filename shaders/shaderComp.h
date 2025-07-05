#pragma once
#include"KnightEnginepch.h"
#include"glad/glad.h"

namespace KnightEngine {


	class KNIGHT_ENGINE_API ShaderComp {
	public:
		ShaderComp(const std::string& vertexPath, const std::string& fragmentPath);
		~ShaderComp();
		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererID;

	};

}