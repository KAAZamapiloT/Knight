#pragma once
#include"Graphics/GraphicsFactory.hpp"
#include<memory>
#include<Graphics/RenderQueue.hpp>
#include"Graphics/Mesh.hpp"
#include"Core/Logger.hpp"
#include"Graphics/Camera.hpp"
#include"shaderComp.h"
namespace Knight{
	class KNIGHT_ENGINE_API Renderer
	{
		using MAT4x4 = glm::mat4x4;
	public:
		static void Init();
		static void BeginFrame(Camera&camera);
		//for debugging to check if its renderer or camera  fault
		static void BeginFrame() {
			RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));
		}
		static void EndFrame();

		static void SubmitCommand(const std::shared_ptr<VertexArray> VAO,const std::shared_ptr<KnightEngine::ShaderComp> S,MAT4x4 Transformation =  glm::mat4(1.0));

		void ClearCommand();
		static inline GraphicsAPI* GetAPI() { return RenderCommand::GetApi(); }
		static inline RenderQueue* GetRenderQueue() { return s_RenderQueue.get(); }
	private:
		
	
	static  std::unique_ptr<RenderQueue> s_RenderQueue;

	struct SceneData {
		glm::mat4x4 ViewProjectionMatrix;
	};


	static SceneData* m_SceneData;
	};
}
