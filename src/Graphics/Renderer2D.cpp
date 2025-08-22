#include "Renderer2D.hpp"
#include"Core/Core.h"
#include"Graphics/VertexArray.hpp"
#include"shaderComp.h"
#include"Graphics/RenderCommand.hpp"
#include"OpenGl/OpenGLShaderComp.hpp"
namespace Knight {
    struct Renderer2DData {
        Ref<VertexArray> QuadVAO;
        Ref<KnightEngine::ShaderComp> Shader;
        glm::mat4 ViewProjectionMatrix; // Store the camera matrix
    };

    static Renderer2DData* s_Data;

    void Renderer2D::Init() {
        s_Data = new Renderer2DData();
        s_Data->QuadVAO = VertexArray::Create();

        float Vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        BufferLayout layout = { { EDataType::Float3, "a_Position" } };
        Ref<VertexBuffer> QuadVB = VertexBuffer::Create(Vertices, sizeof(Vertices));
        QuadVB->SetLayout(layout);

        uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> QuadIB = IndexBuffer::Create(indices, 6);

        s_Data->QuadVAO->AddVertexBuffer(QuadVB);
        s_Data->QuadVAO->SetIndexBuffer(QuadIB);

        s_Data->Shader = KnightEngine::ShaderComp::Create("H:\\GameEngine\\KnightEngine\\KnightCore\\Assets\\Shaders\\Cube.glsl");
    }

    void Renderer2D::Shutdown() {
        delete s_Data;
    }

    void Renderer2D::BeginFrame(const Camera& camera) {
        // Prepare for the frame by clearing the screen and setting up the shader
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

        // Store the camera's matrix so the DrawQuad functions can use it
        s_Data->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		s_Data->Shader->Bind();
        //auto openglShader = std::dynamic_pointer_cast<OpenGLShaderComp>(s_Data->Shader);
        //openglShader->Bind();
        //openglShader->UploadUniformMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);
		// NEW API FOR SHADER UPLOADS
		s_Data->Shader->UploadUniformMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);
		s_Data->Shader->UploadUniformfloat3("u_Transform", { 1.0f, 1.0f, 1.0f });
    }

    void Renderer2D::EndFrame() {
        // In immediate mode, this function doesn't need to do anything.
    }

    void Renderer2D::Flush() {
        // Not used in immediate mode.
    }

    // This is now the main implementation for drawing a colored quad.
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
       // auto openglShader = std::dynamic_pointer_cast<OpenGLShaderComp>(s_Data->Shader);

        // 1. Calculate the unique transformation matrix for this quad.
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        // 2. Upload the transform and color uniforms.
        s_Data->Shader->UploadUniformMat4("u_Transform", transform);
        s_Data->Shader->UploadUniformfloat3("u_Color", { color.r, color.g, color.b });
		s_Data->QuadVAO->Bind();
        // 3. Perform the draw call.
        RenderCommand::DrawIndexed(s_Data->QuadVAO);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
		//auto openglShader = std::dynamic_pointer_cast<OpenGLShaderComp>(s_Data->Shader);
        // 1. Calculate the unique transformation matrix for this rotated quad.
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        // 2. Upload the transform and color uniforms.
        s_Data->Shader->UploadUniformMat4("u_Transform", transform);
        s_Data->Shader->UploadUniformfloat3("u_Color", { color.r, color.g, color.b });
        // 3. Perform the draw call.
        s_Data->QuadVAO->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVAO);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
       // auto openglShader = std::dynamic_pointer_cast<OpenGLShaderComp>(s_Data->Shader);
        // 1. Calculate the unique transformation matrix for this rotated quad.
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        // 2. Upload the transform and color uniforms.
        s_Data->Shader->UploadUniformMat4("u_Transform", transform);
        s_Data->Shader->UploadUniformfloat3("u_Color", { color.r, color.g, color.b });
        // 3. Perform the draw call.
        s_Data->QuadVAO->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVAO);
    }

    // This overload simply calls the main vec3 version.
    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }
	

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tintColor)
	{
      //  auto openglShader = std::dynamic_pointer_cast<OpenGLShaderComp>(s_Data->Shader);
        // 1. Calculate the unique transformation matrix for this rotated quad.
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        // 2. Upload the transform and color uniforms.
        s_Data->Shader->UploadUniformMat4("u_Transform", transform);
        s_Data->Shader->UploadUniformfloat3("u_Color", { tintColor.r, tintColor.g, tintColor.b });
        // Bind the texture
        texture->Bind();
        // 3. Perform the draw call.
        s_Data->QuadVAO->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVAO);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tintColor)
	{
       // auto openglShader = std::dynamic_pointer_cast<OpenGLShaderComp>(s_Data->Shader);
        // 1. Calculate the unique transformation matrix for this rotated quad.
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        // 2. Upload the transform and color uniforms.
        s_Data->Shader->UploadUniformMat4("u_Transform", transform);
        s_Data->Shader->UploadUniformfloat3("u_Color", { tintColor.r, tintColor.g, tintColor.b });
        // Bind the texture
        texture->Bind();
        // 3. Perform the draw call.
        s_Data->QuadVAO->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVAO);
		RenderCommand::DrawIndexed(s_Data->QuadVAO);
	}

}