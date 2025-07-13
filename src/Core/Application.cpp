#include "Core/Application.hpp"
#include "triangle.h"
#include"vector"
#include "shapes.h"
#include "Core/Logger.hpp"
#include"Graphics/Renderer.hpp"
#include"utils/Math.hpp"
#include"OpenGl/OpenGLVertexBuffer.hpp"
#include"OpenGl/OpenGLIndexBuffer.hpp"
#include"Graphics/BufferLayout.hpp"
#include"OpenGl/OpenGLVertexArray.hpp"
//#include"Engine.hpp"
#include"KeyCodes.h"

KnightEngine::Application* KnightEngine::Application::sInstance = nullptr;

namespace KnightEngine {
#define BIND_EVENT_FN(X) std::bind(&X, this, std::placeholders::_1)

    static GLenum ShaderDataType(EDataType E) {
        switch (E) {
        case EDataType::Float:
        case EDataType::Float2:
        case EDataType::Float3:
        case EDataType::Float4:
            return GL_FLOAT;
        case EDataType::Int:
        case EDataType::Int2:
        case EDataType::Int3:
        case EDataType::Int4:
            return GL_INT;
        case EDataType::UInt:
            return GL_UNSIGNED_INT;
        case EDataType::Bool:
            return GL_BOOL;
        case EDataType::Mat2:
        case EDataType::Mat3:
        case EDataType::Mat4:
            return GL_FLOAT;
        default:
            return GL_FLOAT;
        }
    }
    void CheckGLError(const std::string& operation) {
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            KE_TAG_LOG_CRITICAL("OpenGL", "Error after {}: {}", operation, error);
        }
    }
    class ExampleLayer :public  Layer {
    public:
        ExampleLayer() = default;
        ~ExampleLayer() {
            KE_TAG_LOG_WARN("ExampleLayer","DESTROyes");
        }
        void OnImGuiRender() override {
            static char inputBuf[2048] = "";
            static std::vector<std::string> terminalLog;
            static bool scrollToBottom = false;



            ImGui::Begin("Terminal");

            // --- Output region
            ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
            for (const std::string& line : terminalLog)
                ImGui::TextUnformatted(line.c_str());

            if (scrollToBottom)
                ImGui::SetScrollHereY(1.0f); // Scroll to bottom
            scrollToBottom = false;
            ImGui::EndChild();

            // --- Input line
            ImGui::Separator();
            if (ImGui::InputText("Command", inputBuf, IM_ARRAYSIZE(inputBuf), ImGuiInputTextFlags_EnterReturnsTrue)) {
                // On Enter key pressed
                std::string inputStr = inputBuf;
                terminalLog.push_back("> " + inputStr); // Echo command
                inputBuf[0] = '\0'; // Clear input buffer

                // Simulate some output
                terminalLog.push_back("You typed: " + inputStr);
                scrollToBottom = true;
            }
            ImGui::End();

        }


    private:
        char buf[1024];
        float Vol = 0;
        float fontScale = 1.0;
    };
    void InitLogger()
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::trace);

        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("KnightEngine.log", true);
        file_sink->set_level(spdlog::level::trace);

        std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };
        auto logger = std::make_shared<spdlog::logger>("KnightLogger", sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);

        spdlog::set_default_logger(logger);
        spdlog::set_level(spdlog::level::trace);
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
		KE_TAG_LOG_TRACE("LOGGER INIT", "Logger initialized successfully TO TRACE");
    }

    Application::Application(): M_Camera(-1.f, 1.f, -1.f, 1.f, -2.0f, 2.0f)
    {
        InitLogger();
        // Initialize core systems here
        KE_LOG_INFO("Application is starting");

       

        M_Window = std::unique_ptr<Window>(Window::Create(WindowProps("KnightEngine", 1240, 720)));
        M_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
       m_ImGuiLayer = new ImguiLayer();
        if (!sInstance)
            sInstance = this;
        else
            KE_LOG_CRITICAL("Application instance already exists, this should not happen!");
        if (!M_Window) {
            KE_TAG_LOG_CRITICAL("Application", "window is not created ");
        }

        if (!m_ImGuiLayer) {
            KE_TAG_LOG_CRITICAL("Application", "ImGui Layer is not created ");
        }
    PushOverlay(m_ImGuiLayer);
    //    PushOverlay(new  ExampleLayer());

		m_VertexArray = std::shared_ptr<VertexArray>(VertexArray::Create());
        m_VertexArray->Bind();
        float Vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0,0.4,0.3,1.0 ,
             0.5f, -0.5f, 0.0f, 0.0,1.0,0.3,1.0 ,
             0.0f,  0.5f, 0.0f ,0.0,0.0,1.0,1.0 
        };
        std::shared_ptr<VertexBuffer>m_VertexBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(Vertices,sizeof(Vertices)));
        {
            BufferLayout layout = {
                {EDataType::Float3, "aPos"},
                {EDataType::Float4,"aColor", true} // Example of adding a color attribute
            };

            m_VertexBuffer->SetLayout(layout);
        }
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        uint32_t indices[] = { 0, 1, 2 };
        uint32_t indexCount = sizeof(indices) / sizeof(indices[0]);
        std::shared_ptr<IndexBuffer>m_IndexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(indices,indexCount));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
        CheckGLError("bind Index");
        
        //////////////////////////////////////////////
        m_SquareVA.reset(VertexArray::Create());
    
    m_SquareVA->Bind();
    float squareVert[] = {
       -0.75f, -0.75f, 0.0f, 
             0.75f, -0.75f, 0.0f, 
             0.75f,  0.75f, 0.0f ,
              -0.75f,  0.75f, 0.0f 
    };
    std::shared_ptr<VertexBuffer> squareVB = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(squareVert,sizeof(squareVert)));
   squareVB->SetLayout( {
        {EDataType::Float3,"aPosition"},
   
    });
    
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t indexes[] = { 0,1,2,2,3,0 };
    uint32_t indexSize = sizeof(indexes) / sizeof(indexes[0]);
    std::shared_ptr<IndexBuffer> squareIB = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(indexes,indexSize));
    m_SquareVA->SetIndexBuffer(squareIB);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        std::string Vertex = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;  // Add this line
uniform mat4 u_ViewProjectionMatrix;
out vec3 vPosition;
out vec4 vColor;  // Add this line
void main() {
vPosition = aPos; // Pass the vertex position to the fragment shader
vColor = aColor; // Pass the color to the fragment shader
  gl_Position = u_ViewProjectionMatrix*vec4(aPos+0.25, 1.0);
 //gl_Position = vec4(aPos, 1.0);
}
)";

        // Fragment Shader  
        std::string Fragment = R"(
#version 330 core

out vec4 FragColor;
in vec3 vPosition; // Receive the vertex position from the vertex shader
in vec4 vColor; // Receive the color from the vertex shader
void main() {
    FragColor = vColor; // Use the color passed from the vertex shader 
     //FragColor = vec4(vPosition * 0.5 + 0.5, 1.0); // Normalize position to [0, 1] range
}
)";

        std::string Vertex2 = R"(
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 u_ViewProjectionMatrix; 
void main() {
    gl_Position = u_ViewProjectionMatrix*vec4(aPos, 1.0);
}
)";

        // Fragment Shader  
        std::string Fragment2 = R"(
#version 330 core
out vec4 FragColor;

void main() {
  
   FragColor = vec4(0.1,0.1,0.8, 0.2); // Normalize position to [0, 1] range
}
)";
        m_Shader2 = std::make_shared<ShaderComp>(Vertex2, Fragment2);
		m_Shader = std::make_shared<ShaderComp>(Vertex, Fragment);
        if (!m_Shader||!m_Shader2) {  // Assuming you have this method
            KE_TAG_LOG_CRITICAL("ShaderComp","Shader compilation failed!");
        }
}

    Application::~Application()
    {
        // Cleanup resources here
    }

    void Application::Run()
    {
        Knight::RenderCommand rc;
       rc.Init();
       Knight::Renderer m_Renderer;
       m_Renderer.Init();
	  
        // Main game loop
        KE_TAG_LOG_INFO("APPLICATION", "Running Application");
        while (m_Running)
        {
           
            
          

            m_Renderer.BeginFrame(M_Camera);
            m_Renderer.SubmitCommand(m_VertexArray,m_Shader);
            m_Renderer.SubmitCommand(m_SquareVA,m_Shader2);
       
           
         
            // polling for layer events
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }
           
            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();
            M_Window->OnUpdate();
            
           
          
           
        }
		
	
		KE_TAG_LOG_INFO("APPLICATION", "Application is exiting");
		// Shutdown the application
		KE_TAG_LOG_DEBUG("APPLICATION", "Application shutdown initiated");
		KE_TAG_LOG_INFO("APPLICATION", "Application is shutting down");
        KE_TAG_LOG_WARN("Application", "Application shutdown initiated");
        OnShutdown();
        Shutdown();
        KE_TAG_LOG_DEBUG("Application", "Application shutdown complete");
      
    }

    void Application::OnEvent(Event& E)
    {
        //Handleing events here
        EventDispatcher dispatcher(E);
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnwindowResize));
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        //dispatcher.Dispatch<AppTickEvent>(BIND_EVENT_FN(Application::OnAppTick));
        //dispatcher.Dispatch<AppUpdateEvent>(BIND_EVENT_FN(Application::OnAppUpdate));
        //dispatcher.Dispatch<AppRenderEvent>(BIND_EVENT_FN(Application::OnAppRender));
        // Log the event
       // KE_TAG_LOG_INFO("ApplicationEvent:OnEvent", "Event received: {}", E.ToString());

        // unwinnding of stack 
        M_Camera.OnEvent(E);
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(E);
            if (E.IsHandled())
                break; // Stop processing if the event is handled
        }

    }
    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }
    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
    bool Application::OnWindowClose(WindowCloseEvent& E)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnwindowResize(WindowResizeEvent& E)
    {
        m_width = M_Window->GetWidth();
        m_height = M_Window->GetHeight();
        Knight::RenderCommand rw;
        rw.SetViewport(0, 0, m_height-200, m_height-200);
        
        return true;
    }


    void Application::OnShutdown()
    {
        M_Window.reset();

    }



    void Application::Shutdown()
    {
     
        WindowCloseEvent();

    }

 

} // namespace KnightEngine