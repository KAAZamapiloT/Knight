#pragma once
#include"KnightEnginepch.h"
#include"glad/glad.h"
#include"utils/Math.hpp"
namespace KnightEngine {


	class KNIGHT_ENGINE_API ShaderComp {
	public:
		ShaderComp(const std::string& vertexPath, const std::string& fragmentPath);
		~ShaderComp();
		void Bind() const;
		void Unbind() const;
		void UploadUniformMat4(const std::string& name,const glm::mat4 Matrix);

	private:
		uint32_t m_RendererID;

	};

}