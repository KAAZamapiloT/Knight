// --- Engine & Library Includes ---
#include "Engine.hpp"
#include "Knight.hpp"





// --- Inlined Shaders (UPDATED with Lighting) ---
const std::string vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 a_Position;
    layout (location = 1) in vec3 a_Normal;

    uniform mat4 u_ViewProjection;
    uniform mat4 u_Transform;

    out vec3 v_Normal;
    out vec3 v_FragPos;

    void main() { 
        gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0); 
        v_FragPos = vec3(u_Transform * vec4(a_Position, 1.0));
        // Transform normals to world space
        v_Normal = mat3(transpose(inverse(u_Transform))) * a_Normal;
    }
)";

const std::string fragmentShaderSource = R"(
    #version 330 core
    layout (location = 0) out vec4 color;
    
    in vec3 v_Normal;
    in vec3 v_FragPos;

    uniform vec3 u_Color;
    uniform vec3 u_LightPos;

    void main() { 
        // Basic Lambertian diffuse lighting
        vec3 norm = normalize(v_Normal);
        vec3 lightDir = normalize(u_LightPos - v_FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * vec3(1.0); // White light

        // Add a bit of ambient light so the dark faces aren't pure black
        float ambientStrength = 0.2;
        vec3 ambient = ambientStrength * vec3(1.0);

        vec3 result = (ambient + diffuse) * u_Color;
        color = vec4(result, 1.0); 
    }
)";


/**
 * @class ExampleLayer
 * @brief A custom layer that renders a grid of spinning 3D cubes.
 */
class ExampleLayer : public KnightEngine::Layer {
public:
    ExampleLayer() : Layer("3DCubeLayer"), m_CameraController(1280.0f / 720.0f, Knight::ECameraType::Perspective) {
        // --- Setup Graphics Objects for a 3D Cube ---

       // Create a 3D Cube Mesh with correct, non-shared vertices for proper lighting
        float vertices[] = {
            // Positions           // Normals
            // Back face
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            // Front face
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            // Left face
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            // Right face
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             // Bottom face
             -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
              0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
              0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
              0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             // Top face
             -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
              0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
              0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
              0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
             -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f
        };

        // Since we defined each face with 6 vertices, we create a simple, linear index buffer.
        uint32_t indices[36];
        for (uint32_t i = 0; i < 36; i++) {
            indices[i] = i;
        }

        auto cubeVB = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));
        // FIX: Create and set the index buffer.
        auto cubeIB = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(indices, 36));

        BufferLayout layout = {
            { EDataType::Float3, "a_Position" },
            { EDataType::Float3, "a_Normal" }
        };
        cubeVB->SetLayout(layout);
        m_CubeVA = VertexArray::Create();
        m_CubeVA->AddVertexBuffer(cubeVB);
        m_CubeVA->SetIndexBuffer(cubeIB); // Set the index buffer on the VAO

        m_Shader = KnightEngine::ShaderComp::Create("SceneShader", vertexShaderSource, fragmentShaderSource);
        KE_CORE_ASSERT(m_Shader, "Failed to create Shader!");
    }

    void OnUpdate(KnightEngine::TimeStamp ts) override {
        m_CameraController.OnUpdate(ts);
        m_Rotation += (float)ts * 20.0f;

        Knight::Renderer::BeginFrame(m_CameraController.GetCamera());

        auto openglShader = std::static_pointer_cast<OpenGLShaderComp>(m_Shader);
        openglShader->Bind();
        openglShader->UploadUniformMat4("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());
        openglShader->UploadUniformfloat3("u_Color", m_ObjectColor);

        openglShader->UploadUniformfloat3("u_LightPos", m_LightPos);

        float size = 0.5f;
        float padding = 0.2f;

        // --- 3D Rendering Logic ---
        for (int y = 0; y < m_GridSize; y++) {
            for (int x = 0; x < m_GridSize; x++) {
                glm::vec3 pos(x * (size + padding), 0.0f, y * (size + padding));
                glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(size));
                glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.5f, 1.0f, 0.0f));
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * rotation * scale;
                openglShader->UploadUniformMat4("u_Transform", transform);
                Knight::Renderer::SubmitCommand(m_CubeVA, m_Shader, transform);
            }
        }

        Knight::Renderer::EndFrame();
    }

    void OnEvent(Event& e) override {
        m_CameraController.OnEvent(e);

    }

    void OnImGuiRender() override {
        ImGui::Begin("Settings");

        ImGui::ColorEdit3("Object Color", glm::value_ptr(m_ObjectColor));
        ImGui::SliderInt("Grid Size", &m_GridSize, 1, 10);
        ImGui::DragFloat3("Light Position", glm::value_ptr(m_LightPos), 0.1f);

        ImGui::Separator();

        ImGui::Text("Camera Info");

        const auto& camera = m_CameraController.GetCamera();
        const auto& camPos = camera.GetPosition();
        ImGui::Text("Position: (%.2f, %.2f, %.2f)", camPos.x, camPos.y, camPos.z);
        const auto& camRot = camera.GetRotation();
        glm::vec3 euler = glm::degrees(glm::eulerAngles(camRot));
        ImGui::Text("Rotation (Euler): (%.2f, %.2f, %.2f)", euler.x, euler.y, euler.z);

        ImGui::End();
    }

private:
    Knight::Ref<VertexArray> m_CubeVA;
    std::shared_ptr<KnightEngine::ShaderComp> m_Shader;
    Knight::CameraController m_CameraController;
    glm::vec3 m_ObjectColor = { 0.8f, 0.2f, 0.3f };
    glm::vec3 m_LightPos = { 1.2f, 1.0f, 2.0f };
    int m_GridSize = 5;
    float m_Rotation = 0.0f;
};

// --- Main Application Entry Point ---
int main(int argc, char** argv)
{
    auto app = new KnightEngine::Application();
    app->PushLayer(new ExampleLayer());
    //app->PushLayer(new Example2D());
    app->Run();
    delete app;
    return 0;
}
