#pragma once
#include"Graphics/GraphicsFactory.hpp"
#include<memory>
#include"Core/Logger.hpp"

namespace Knight{
	class KNIGHT_ENGINE_API Renderer
	{
	public:
		void Init();
		void BeginFrame();
		void EndFrame();
		void ClearColor(float r, float g, float b, float a);
	private:
		
	static  std::unique_ptr<GraphicsAPI> s_API;
	};
}
