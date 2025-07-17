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

    Application::Application()
    {
        InitLogger();
        // Initialize core systems here
        KE_LOG_INFO("Application is starting");
        M_Window = std::unique_ptr<Window>(Window::Create(WindowProps("KnightEngine", 1240, 720)));
        M_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
       m_ImGuiLayer = new ImguiLayer();
       m_Renderer->Init();
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
       M_Window->SetVSync(false);
        // Main game loop
        KE_TAG_LOG_INFO("APPLICATION", "Running Application");
        while (m_Running)
        {
            float time = (float)SDL_GetTicks();
            TimeStamp timestamp=time-m_LastTime;
            m_LastTime = time;
            // polling for layer events
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate(timestamp);
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
        Knight::RenderCommand R;
        m_width = E.GetWidth();
        m_height = E.GetHeight();
        R.SetViewport(0, 0, E.GetWidth(), E.GetHeight());
        
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