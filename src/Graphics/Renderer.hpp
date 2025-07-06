#pragma once
#include"Graphics/GraphicsFactory.hpp"
#include<memory>
#include<Graphics/RenderQueue.hpp>
#include"Graphics/Mesh.hpp"
#include"Core/Logger.hpp"

namespace Knight{
	class KNIGHT_ENGINE_API Renderer
	{
	public:
		void Init();
		void BeginFrame();
		void SubmitCommand(RenderCommand& q);
		
		void EndFrame();

		void ClearCommand();
		static inline GraphicsAPI* GetAPI() { return s_API.get(); }
		static inline RenderQueue* GetRenderQueue() { return s_RenderQueue.get(); }
	private:
		
	static  std::unique_ptr<GraphicsAPI> s_API;
	static  std::unique_ptr<RenderQueue> s_RenderQueue;
	
	};
}
