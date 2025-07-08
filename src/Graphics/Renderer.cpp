#include "Renderer.hpp"
#include"RenderCommand.hpp"
#include "Core/Logger.hpp"

namespace Knight {
    std::unique_ptr<GraphicsAPI> Renderer::s_API = nullptr;
    std::unique_ptr<RenderQueue> Renderer::s_RenderQueue = std::make_unique<RenderQueue>();
    void Renderer::Init() {
        s_API = CreateGraphicsAPI();
        if (!s_RenderQueue) {
            KE_TAG_LOG_CRITICAL("Renderer", "Failed to create RenderQueue instance");
            return;
        }
        if (!s_API) {
            KE_TAG_LOG_CRITICAL("Renderer", "Failed to create GraphicsAPI instance");
            return;
        }
        s_API->Init();

        KE_TAG_LOG_INFO("Renderer", "Renderer initialized successfully");
    }

    void Renderer::BeginFrame() {
        s_API->Clear(0.1f, 0.1f, 0.1f, 1.0f);
    }

    





    void Renderer::EndFrame() {
        for (auto& it : s_RenderQueue->GetCommands()) {
            
     }

    }

    void Renderer::SubmitCommand(const std::shared_ptr<VertexArray> VAO)
    {
        //TEMPRORY IMPL
        std::unique_ptr<RenderCommand> r;
       r->DrawIndexed(VAO);

    }

    void Renderer::ClearCommand()
    {
        s_RenderQueue.get()->ClearCommands();
    }







}