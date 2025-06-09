#pragma once
#include"Graphics/GraphicsFactory.hpp"
#include<memory>
#include<Graphics/RenderQueue.hpp>
#include"Core/Logger.hpp"

namespace Knight{
	class KNIGHT_ENGINE_API Renderer
	{
	public:
		void Init();
		void BeginFrame();
		void SumbitCommand(RenderCommand& q);
		void EndFrame();

		void ClearCommand();
		
	private:
		
	static  std::unique_ptr<GraphicsAPI> s_API;
	static  std::unique_ptr<RenderQueue> s_RenderQueue;
	
	};
}
