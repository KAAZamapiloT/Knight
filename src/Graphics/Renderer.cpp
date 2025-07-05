#include "Renderer.hpp"

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

    void Renderer::SubmitCommand(RenderCommand& q)
    {
        // CAN I ADD A CHECK HERE SO THAT USELESS COMMANDS DONT GET SUBMITTED
        s_RenderQueue.get()->AddCommand(q);
    }





    void Renderer::EndFrame() {
        // Placeholder – for post-processing, etc.
        // HERE EVERY COMMAND IN RENDER QUEUE SHOULD END

    }

    void Renderer::ClearCommand()
    {
        s_RenderQueue.get()->ClearCommands();
    }







}