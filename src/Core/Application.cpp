#include "Core/Application.hpp"
#include "Core/Logger.hpp"
#include "Graphics/RenderCommand.hpp"
#include <functional>

namespace KnightEngine {

    // --- Static Member Definitions ---
    // This is where the static members declared in the header are actually created in memory.
    Application* Application::sInstance = nullptr;
    // This line provides the definition for the static renderer, fixing the linker error.
    Knight::Renderer Application::m_Renderer;

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    // Private helper function to initialize the logger
    void InitLogger()
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("KnightEngine.log", true);
        file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
        std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };
        auto logger = std::make_shared<spdlog::logger>("KnightLogger", sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);
        spdlog::set_default_logger(logger);
        KE_TAG_LOG_TRACE("Logger", "Logging system initialized.");
    }

    Application::Application()
    {
        InitLogger();
        KE_CORE_ASSERT(!sInstance, "Application instance already exists!");
        sInstance = this;

        // Create the window and its graphics context FIRST.
        M_Window = Knight::Scope<Window>(Window::Create(WindowProps("KnightEngine", m_width, m_height)));
        KE_CORE_ASSERT(M_Window, "Window could not be created!");
        M_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        // NOW that a context exists, initialize the static renderer.
        m_Renderer.Init();

        m_ImGuiLayer = new ImguiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
        KE_TAG_LOG_INFO("Application", "Destructor called. Initiating shutdown.");
        Shutdown();
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

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnwindowResize));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.IsHandled())
                break;
        }
    }

    void Application::Run()
    {
        KE_TAG_LOG_INFO("Application", "Starting main loop.");

        while (m_Running)
        {
            // The screen clear is now correctly handled by the Renderer's BeginFrame method.

            float time = (float)SDL_GetTicks() / 1000.0f;
            TimeStamp timestep = time - m_LastTime;
            m_LastTime = time;
            if (!m_Minimized) {
                for (Layer* layer : m_LayerStack)
                {
                    layer->OnUpdate(timestep);
                }
            }
           

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            M_Window->OnUpdate();
        }

        KE_TAG_LOG_INFO("Application", "Exiting main loop.");
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnwindowResize(WindowResizeEvent& e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_width = e.GetWidth();
        m_height = e.GetHeight();
        m_Minimized = false;
        // Correct: Use RenderCommand as a static utility class.
        Knight::RenderCommand::SetViewport(0, 0, e.GetWidth(), e.GetHeight());

        return false;
    }

    void Application::OnShutdown()
    {
        // Client application can override this to perform its own cleanup.
    }

    void Application::Shutdown()
    {
        KE_TAG_LOG_TRACE("Application", "Calling client OnShutdown hook.");
        OnShutdown();
    }

}
