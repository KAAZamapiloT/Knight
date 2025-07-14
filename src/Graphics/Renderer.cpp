#include "Renderer.hpp"
#include"RenderCommand.hpp"
#include "Core/Logger.hpp"
#include"OpenGl/OpenGLShaderComp.hpp"
namespace Knight {
    std::unique_ptr<GraphicsAPI> Renderer::s_API = nullptr;
    std::unique_ptr<RenderQueue> Renderer::s_RenderQueue = std::make_unique<RenderQueue>();
    Renderer::SceneData* Renderer::m_SceneData=new Renderer::SceneData;

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

    void Renderer::BeginFrame(Camera& camera) {
        s_API->Clear(0.1f, 0.1f, 0.1f, 1.0f);
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    





    void Renderer::EndFrame() {
        for (auto& it : s_RenderQueue->GetCommands()) {
            
     }

    }

    void Renderer::SubmitCommand(const std::shared_ptr<VertexArray> VAO, const std::shared_ptr<KnightEngine::ShaderComp> S, MAT4x4 Transformation)
    {
        //TEMPRORY IMPL
        std::dynamic_pointer_cast<OpenGLShaderComp>(S)->Bind();
        std::dynamic_pointer_cast<OpenGLShaderComp>(S)->UploadUniformMat4("u_ViewProjectionMatrix", m_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShaderComp>(S)->UploadUniformMat4("u_Transform", Transformation);
        std::unique_ptr<RenderCommand> r;
       r->DrawIndexed(VAO);

    }

    void Renderer::ClearCommand()
    {
        s_RenderQueue.get()->ClearCommands();
    }







}