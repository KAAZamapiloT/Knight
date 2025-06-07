#include "Renderer.hpp"

#include "Core/Logger.hpp"
namespace Knight {
    std::unique_ptr<GraphicsAPI> Renderer::s_API = nullptr;
	
    void Renderer::Init() {
     s_API = CreateGraphicsAPI();
       if (!s_API) {
			KE_TAG_LOG_CRITICAL("Renderer", "Failed to create GraphicsAPI instance");
            return;
        }
       s_API->Init();
		KE_TAG_LOG_INFO("Renderer", "Renderer initialized successfully");
    }

    void Renderer::BeginFrame() {
       // s_API->Clear(0.1f, 0.1f, 0.1f, 1.0f);
    }
     
    void Renderer::EndFrame() {
        // Placeholder – for post-processing, etc.
    }

    void Renderer::ClearColor(float r, float g, float b, float a)
    {
	s_API->Clear(r, g, b, a);
    }

   

   

}
