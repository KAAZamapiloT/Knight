#pragma once
#include"EngineApi.hpp"
#include "KnightEnginepch.h"
#include"utils/Math.hpp"
#include"shaderComp.h"
#include"glad/glad.h"
class KNIGHT_ENGINE_API OpenGLShaderComp:public KnightEngine::ShaderComp
{
public:
	OpenGLShaderComp(const std::string& name,const std::string& vertexSource, const std::string& fragmentSource);
	OpenGLShaderComp(const std::string& filepath);
	virtual ~OpenGLShaderComp();
	void Bind() const override;
	void Unbind() const override;
	void UploadUniformMat4(const std::string& name, const glm::mat4 Matrix) override;
	void UploadUniformMat3(const std::string& name, const glm::mat3 Matrix) override;
	void UploadUniformfloat4(const std::string& name, const glm::vec4 col) override;
	void UploadUniformfloat3(const std::string& name, const glm::vec3 col) override;
	void UploadUniformfloat2(const std::string& name, const glm::vec2 col) override;
	void UploadUniformint(const std::string& name, const int col) override;

	const std::string& GetName() const override { return m_Name; }

	void SetFloat3(std::string name,const glm::vec3& value) override;
	void SetFloat2(std::string name,const glm::vec2& value) override;
	void SetMat4(std::string name,const glm::mat4& value) override;
private:
	void Compile(const std::unordered_map<GLenum, std::string>&ShaderSources);
	std::unordered_map<GLenum,std::string> Preprocess(const std::string& ShaderString);
	std::string ReadFile(const std::string&filepath);
	
private:
	uint32_t m_RendererID;
	std::string m_Name;
};
