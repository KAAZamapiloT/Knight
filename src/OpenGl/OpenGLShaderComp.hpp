#pragma once
#include"EngineApi.hpp"
#include "KnightEnginepch.h"
#include"utils/Math.hpp"
#include"shaderComp.h"
#include"glad/glad.h"
class KNIGHT_ENGINE_API OpenGLShaderComp:public KnightEngine::ShaderComp
{
public:
	OpenGLShaderComp(const std::string& vertexSource, const std::string& fragmentSource);
	virtual ~OpenGLShaderComp();
	void Bind() const override;
	void Unbind() const override;
	void UploadUniformMat4(const std::string& name, const glm::mat4 Matrix) ;
	void UploadUniformMat3(const std::string& name, const glm::mat3 Matrix);
	void UploadUniformfloat4(const std::string& name, const glm::vec4 col) ;
	void UploadUniformfloat3(const std::string& name, const glm::vec3 col);
	void UploadUniformfloat2(const std::string& name, const glm::vec2 col);
	void UploadUniformint(const std::string& name, const int col);
private:
	uint32_t m_RendererID;
};
