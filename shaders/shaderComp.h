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
		//void UploadUniformMat4(const std::string& name,const glm::mat4 Matrix);
		//void UploadUniformfloat4(const std::string& name, const glm::vec4 col);

		static ShaderComp* Create(const std::string& VertexSource,const std::string& FragmentSource);
		static ShaderComp* Create(const std::string& filepath);
	};

}