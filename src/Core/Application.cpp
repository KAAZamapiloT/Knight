#include "Core/Application.hpp"
#include "triangle.h"
#include"vector"
#include "shapes.h"
#include "Core/Logger.hpp"
#include"Graphics/Renderer.hpp"
#include"utils/Math.hpp"
#include"OpenGl/OpenGLVertexBuffer.hpp"
#include"OpenGl/OpenGLIndexBuffer.hpp"
//#include"Engine.hpp"
#include"KeyCodes.h"
KnightEngine::Application* KnightEngine::Application::sInstance = nullptr;

namespace KnightEngine {
#define BIND_EVENT_FN(X) std::bind(&X, this, std::placeholders::_1)

    
    class ExampleLayer :public  Layer {
    public:
        ExampleLayer() = default;
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
        console_sink->set_level(spdlog::level::debug);

        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("KnightEngine.log", true);
        file_sink->set_level(spdlog::level::debug);

        std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };
        auto logger = std::make_shared<spdlog::logger>("KnightLogger", sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::debug);
        logger->flush_on(spdlog::level::debug);

        spdlog::set_default_logger(logger);
        spdlog::set_level(spdlog::level::debug);
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
    }

    Application::Application()
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
        PushOverlay(new  ExampleLayer());
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float Vertices[] = {
            -0.5f, -0.5f, 0.0f,  // Bottom left
             0.5f, -0.5f, 0.0f,  // Bottom right
             0.0f,  0.5f, 0.0f   // Top center
        };
		m_VertexBuffer = std::make_unique<OpenGLVertexBuffer>(Vertices, sizeof(Vertices));
		m_VertexBuffer->Bind();
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		
        uint32_t indices[] = { 0, 1, 2 };
        m_IndexBuffer = std::make_unique<OpenGLIndexBuffer>(indices,sizeof(indices));
		m_IndexBuffer->Bind();
      
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        std::string Vertex = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
out vec3 vPosition;
void main() {
vPosition = aPos; // Pass the vertex position to the fragment shader
    gl_Position = vec4(aPos, 1.0);
}
)";

        // Fragment Shader  
        std::string Fragment = R"(
#version 330 core
out vec4 FragColor;
in vec3 vPosition; // Receive the vertex position from the vertex shader
void main() {
    FragColor = vec4(vPosition+0.25, 1.0);  // Solid red
}
)";
		m_Shader = std::make_unique<ShaderComp>(Vertex, Fragment);
        if (!m_Shader) {  // Assuming you have this method
            KE_TAG_LOG_CRITICAL("ShaderComp","Shader compilation failed!");
        }
    }

    Application::~Application()
    {
        // Cleanup resources here
    }

    void Application::Run()
    {

        
       // Knight::Renderer R;
        Knight::RenderCommand rc;
       rc.Init();
	   rc.SetViewport(0, 0, m_width, m_height);
	  
	   // Initialize the renderer
       // R.Init();
        // Main game loop
        KE_TAG_LOG_INFO("APPLICATION", "Running Application");
        while (m_Running)
        {

            rc.ClearColor(0.1f, 0.0, 0.1, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            glBindVertexArray(m_VertexArray);
            m_Shader->Bind();
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            // polling for layer events
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }
            // This polls SDL events, invokes your callbacks, then swaps buffers.
            M_Window->OnUpdate();
           // R.BeginFrame();
            // R.SubmitCommandBuffer();
          //  R.EndFrame();
           
            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();
            
           
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
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        //dispatcher.Dispatch<AppTickEvent>(BIND_EVENT_FN(Application::OnAppTick));
        //dispatcher.Dispatch<AppUpdateEvent>(BIND_EVENT_FN(Application::OnAppUpdate));
        //dispatcher.Dispatch<AppRenderEvent>(BIND_EVENT_FN(Application::OnAppRender));
        // Log the event
        KE_TAG_LOG_INFO("ApplicationEvent", "Event received: {}", E.ToString());

        // unwinnding of stack 
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


    void Application::OnShutdown()
    {
        M_Window.reset();

    }



    void Application::Shutdown()
    {

        WindowCloseEvent();

    }

} // namespace KnightEngine