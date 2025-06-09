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

    void Renderer::SumbitCommand(RenderCommand& q)
    {
		s_RenderQueue.get()->AddCommand(q);
    }
     
    void Renderer::EndFrame() {
        // Placeholder – for post-processing, etc.
    }

    void Renderer::ClearCommand()
    {
		s_RenderQueue.get()->ClearCommands();
    }

  

   

   

}
