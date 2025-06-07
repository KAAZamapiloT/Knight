#pragma once
#include"Graphics/GraphicsApi.hpp"
#include<memory>
#include"Core/Logger.hpp"
namespace Knight{
	class KNIGHT_ENGINE_API Renderer
	{
	public:
		void Init();
		void BeginFrame();
		void EndFrame();
		
	private:
		//static GraphicsAPI* GetAPI();
		//static std::unique_ptr<GraphicsAPI> s_API;
	};
}
