#include "Core/Application.hpp"
#include "triangle.h"
#include"vector"
#include "shapes.h"
#include "Core/Logger.hpp"
#include"Graphics/Renderer.hpp"
#include"utils/Math.hpp"
//#include"Engine.hpp"
#include"KeyCodes.h"
KnightEngine::Application* KnightEngine::Application::sInstance = nullptr;

namespace KnightEngine {
#define BIND_EVENT_FN(X) std::bind(&X, this, std::placeholders::_1)
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

// Implementation of Application class

//static Application* Application::sInstance = nullptr;
Application::Application()
{
	InitLogger();
    // Initialize core systems here
	KE_LOG_INFO("Application is starting");
	M_Window = std::unique_ptr<Window>(Window::Create(WindowProps("KnightEngine", 1240, 720)));
    M_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	if (!sInstance)
		sInstance = this;
	else
		KE_LOG_CRITICAL("Application instance already exists, this should not happen!");
	
}

Application::~Application()
{
    // Cleanup resources here
}

void Application::Run()
{
   /* if (!Init_OpenGL()) {
      //  std::cerr << "OPEN_GL Initialization failed!" << std::endl;
		KE_LOG_CRITICAL("OPEN_GL Initialization failed!");
        return;
    }
    if (!Init_Imgui()) {
       // std::cerr << "IMGUI Initialization failed!" << std::endl;
		KE_LOG_CRITICAL("IMGUI Initialization failed!");
        return;
    }
    */
    Triangle tri;
    Shapes sh;
	Knight::Renderer R;
    Knight::RenderCommand rc;
	
    float freq = 0.1f;
	float f = 0.0f;
    float blue = glm::sin(f * freq);
	float ep = glm::sin(f);
    R.Init();
    sh.InitLineShader();
    
    tri.Init();
    R.Init();
    rc.Init();
    // Main game loop
    KE_LOG_INFO("Running Application");
    while (m_Running)
    {
		// polling for layer events
		for (Layer* layer : m_LayerStack)
		{
			layer->OnUpdate();
		}
        // This polls SDL events, invokes your callbacks, then swaps buffers.
        M_Window->OnUpdate();
       
		
        // === ImGui new frame ===
       // ImGui_ImplOpenGL3_NewFrame();
       // ImGui_ImplSDL3_NewFrame();
       // ImGui::NewFrame();

        // === Your ImGui UI ===
       // OnInit_Imgui();

        // === Rendering ===
      /*  glViewport(0, 0, M_Window->GetWidth(), M_Window->GetHeight());
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        */
        blue = (glm::sin(f * freq) + 1.0f) * 0.5f;

        R.BeginFrame();
        // R.SubmitCommandBuffer();
        R.EndFrame();

        rc.ClearColor(0.1f, blue, 0.1f, 1.0f);

        tri.Render();
        sh.render();

        // === ImGui render ===
        //ImGui::Render();
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        f += 0.01f;
    }
	KE_LOG_CRITICAL("Application is shutting down");
	OnShutdown();
	Shutdown();
	KE_LOG_DEBUG("Application shutdown initiated");
	KE_TAG_LOG_WARN("Application", "Application shutdown initiated");
	KE_TAG_LOG_DEBUG("Application", "Application shutdown complete");
	KE_LOG_CRITICAL("Application shutdown complete");
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
   /* ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();


    SDL_GL_DestroyContext(m_Context);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
    */
    
    WindowCloseEvent();
	
}

} // namespace KnightEngine
