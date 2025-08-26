#include "Renderer2D.hpp"
#include "Core/Core.h"
#include "Graphics/VertexArray.hpp"
#include "shaderComp.h"
#include "Graphics/RenderCommand.hpp"
#include "OpenGl/OpenGLShaderComp.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Knight {

    struct Renderer2DData {
        Ref<VertexArray> QuadVAO;
        Ref<KnightEngine::ShaderComp> FlatColorShader;
        Ref<KnightEngine::ShaderComp> TextureShader;
        glm::mat4 ViewProjectionMatrix; // Store the camera matrix for the frame
    };

    static std::unique_ptr<Renderer2DData> s_Data;

    void Renderer2D::Init() {
        s_Data = std::make_unique<Renderer2DData>();
        s_Data->QuadVAO = VertexArray::Create();

        // Vertex data now includes texture coordinates for our universal quad
        float vertices[] = {
            // Positions      // Tex Coords
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        BufferLayout layout = {
            { EDataType::Float3, "a_Position" },
            { EDataType::Float2, "a_TexCoord" }
        };
        Ref<VertexBuffer> quadVB = VertexBuffer::Create(vertices, sizeof(vertices));
        quadVB->SetLayout(layout);

        uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> quadIB = IndexBuffer::Create(indices, 6);

        s_Data->QuadVAO->AddVertexBuffer(quadVB);
        s_Data->QuadVAO->SetIndexBuffer(quadIB);

        s_Data->FlatColorShader = KnightEngine::ShaderComp::Create("H:\\GameEngine\\KnightEngine\\KnightCore\\Assets\\Shaders\\Cube.glsl");
        s_Data->TextureShader = KnightEngine::ShaderComp::Create("H:\\GameEngine\\KnightEngine\\KnightCore\\Assets\\Shaders\\Texture.glsl");
    }

    void Renderer2D::Shutdown() {
        s_Data.reset();
    }

    void Renderer2D::BeginFrame(const Camera& camera) {
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

        // Store the camera's matrix once for the entire frame.
        // We no longer bind or upload to any specific shader here.
        s_Data->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer2D::EndFrame() {
        // In immediate mode, this function doesn't need to do anything.
    }

    void Renderer2D::Flush() {
        // Not used in immediate mode.
    }

    // --- DrawQuad Implementations ---

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        s_Data->FlatColorShader->Bind();
        s_Data->FlatColorShader->UploadUniformMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        s_Data->FlatColorShader->UploadUniformMat4("u_Transform", transform);
        s_Data->FlatColorShader->UploadUniformfloat3("u_Color", { color.r, color.g, color.b });

        s_Data->QuadVAO->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVAO);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tintColor)
    {
        s_Data->TextureShader->Bind();

        // FIX: Upload the camera's ViewProjection matrix to the texture shader.
        s_Data->TextureShader->UploadUniformMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);

        texture->Bind(0);
        s_Data->TextureShader->UploadUniformint("u_Texture", 0);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        s_Data->TextureShader->UploadUniformMat4("u_Transform", transform);
        s_Data->TextureShader->UploadUniformfloat3("u_Color", { tintColor.r, tintColor.g, tintColor.b });

        s_Data->QuadVAO->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVAO);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
       s_Data->FlatColorShader->Bind();
        s_Data->FlatColorShader->UploadUniformMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data->FlatColorShader->UploadUniformMat4("u_Transform", transform);
        s_Data->FlatColorShader->UploadUniformfloat3("u_Color", { color.r, color.g, color.b });
        s_Data->QuadVAO->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVAO);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tintColor)
    {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tintColor);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tintColor)
    {
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->UploadUniformMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);
        texture->Bind(0);
        s_Data->TextureShader->UploadUniformint("u_Texture", 0);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data->TextureShader->UploadUniformMat4("u_Transform", transform);
        s_Data->TextureShader->UploadUniformfloat3("u_Color", { tintColor.r, tintColor.g, tintColor.b });
        s_Data->QuadVAO->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVAO);
    }


    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tintColor)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture, tintColor);
	}


}
