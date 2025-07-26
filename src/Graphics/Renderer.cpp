#include "Graphics/Renderer.hpp"
#include "Graphics/RenderCommand.hpp" // Renderer now uses RenderCommand
#include "Core/Logger.hpp"
#include "OpenGl/OpenGLShaderComp.hpp"

namespace Knight {

    // The Renderer no longer owns the API. It only owns scene-level data.
    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    /**
     * @brief Initializes the rendering system.
     * @details This function now correctly delegates the low-level API initialization
     * to the RenderCommand class.
     */
    void Renderer::Init() {
        RenderCommand::Init(); // Tell the command dispatcher to set itself up.
        KE_TAG_LOG_INFO("Renderer", "Renderer initialized successfully.");
    }

    void Renderer::BeginFrame(Camera& camera) {
        // High-level frame setup
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

   void Renderer::EndFrame() {
        // High-level frame cleanup
        RenderCommand::Clear(); // Clear the screen with the set clear color
       
   }

    /**
     * @brief Submits a mesh to be drawn.
     * @details This high-level function prepares the shader and then tells the
     * low-level RenderCommand to perform the actual draw call.
     */
    void Renderer::SubmitCommand(const std::shared_ptr<VertexArray> VAO, const std::shared_ptr<KnightEngine::ShaderComp> S, MAT4x4 Transformation)
    {
        auto openglShader = std::dynamic_pointer_cast<OpenGLShaderComp>(S);
        if (!openglShader) return;

        openglShader->Bind();
        openglShader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        openglShader->UploadUniformMat4("u_Transform", Transformation);

        RenderCommand::DrawIndexed(VAO);
    }
    void Renderer::ClearCommand()
    {
    }
}
