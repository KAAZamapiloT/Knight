#include "Renderer.hpp"

namespace Knight {

   // std::unique_ptr<GraphicsAPI> Renderer::s_API = std::make_unique<OpenGLGraphicsAPI>();

    void Renderer::Init() {
     //   s_API->Init();
		KE_TAG_LOG_INFO("Renderer", "Renderer initialized successfully");
    }

    void Renderer::BeginFrame() {
       // s_API->Clear(0.1f, 0.1f, 0.1f, 1.0f);
    }
     
    void Renderer::EndFrame() {
        // Placeholder – for post-processing, etc.
    }

    //GraphicsAPI* Renderer::GetAPI() {
        //return s_API.get();
		
    //}

}
