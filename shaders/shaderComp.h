#pragma once
#include"KnightEnginepch.h"
#include"glad/glad.h"
#include"utils/Math.hpp"
namespace KnightEngine {


	class KNIGHT_ENGINE_API ShaderComp {
	public:
	
		virtual ~ShaderComp(){}
		virtual void Bind() const = 0;
			virtual void Unbind() const = 0;
		virtual void UploadUniformMat4(const std::string& name,const glm::mat4 Matrix)=0;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3 Matrix) = 0;
		virtual void UploadUniformfloat4(const std::string& name, const glm::vec4 col)=0;
		virtual void UploadUniformfloat3(const std::string& name, const glm::vec3 col)=0;
		virtual void UploadUniformfloat2(const std::string& name, const glm::vec2 col)=0;
		virtual void UploadUniformint(const std::string& name, int value) = 0;


		//
		virtual void SetFloat3(std::string name,const glm::vec3& value) = 0;
		virtual void SetFloat2(std::string name,const glm::vec2& value) = 0;
		virtual void SetMat4(std::string name,const glm::mat4& value) = 0;
		
		
		virtual	const std::string& GetName()const = 0 ;
		static Knight::Ref<KnightEngine::ShaderComp> Create(const std::string&name,const std::string& VertexSource,const std::string& FragmentSource);
		static Knight::Ref<KnightEngine::ShaderComp> Create(const std::string& filepath);

	};
	class KNIGHT_ENGINE_API ShaderLibray {
	public:
		void Add(const std::string& name, Knight::Ref<ShaderComp>& S);
		void Add(const Knight::Ref<ShaderComp>& S);
		Knight::Ref<ShaderComp> Load(const std::string filepath);
		Knight::Ref<ShaderComp> Load(const std::string name,const std::string filepath);
		Knight::Ref<ShaderComp> Get(const std::string&name);
		bool Exists(const std::string& name) { return m_ShaderMap.find(name) != m_ShaderMap.end(); }
	private:
		std::unordered_map<std::string, Knight::Ref<ShaderComp>> m_ShaderMap;
	};
}