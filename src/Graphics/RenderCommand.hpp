#pragma once
#include"Graphics/GraphicsFactory.hpp"
#include<memory>
#include"Core/Logger.hpp"
namespace Knight {
	class KNIGHT_ENGINE_API RenderCommand
	{
	public:
		RenderCommand();
		void Init()
		{
			s_API = CreateGraphicsAPI();
			if (!s_API) {
				KE_TAG_LOG_CRITICAL("RenderCommand", "Failed to create GraphicsAPI instance");
				return;
			}
			s_API->Init();
			KE_TAG_LOG_INFO("RenderCommand", "RenderCommand initialized successfully");
		}
		//void BindVertex();
		void ClearColor(float r, float g, float b, float a) {
			s_API->Clear(r, g, b, a);
		}
		void SetViewport(int x, int y, int width, int height)
		{
			s_API->SetViewport(x, y, width, height);
		}
		//void BindArray();
		//void DrawIndexed();
	private:
		static std::unique_ptr<GraphicsAPI> s_API;
	};
}


