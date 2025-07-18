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
	OpenGLShaderComp(const std::string& filepath);
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
	void Compile(const std::unordered_map<GLenum, std::string>&ShaderSources);
	std::unordered_map<GLenum,std::string> Preprocess(const std::string& ShaderString);
	std::string ReadFile(const std::string&filepath);
private:
	uint32_t m_RendererID;
};
