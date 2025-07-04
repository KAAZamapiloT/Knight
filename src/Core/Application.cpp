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

    class ExampleLayer :public Layer {
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

// Implementation of Application class

//static Application* Application::sInstance = nullptr;
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
}

Application::~Application()
{
    // Cleanup resources here
}

void Application::Run()
{
  
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
        blue = (glm::sin(f * freq) + 1.0f) * 0.5f;

        R.BeginFrame();
        // R.SubmitCommandBuffer();
        R.EndFrame();

        rc.ClearColor(0.1f, blue, glm::sin(blue), 1.0f);

        tri.Render();
        sh.render();


        f += 0.01f;

        m_ImGuiLayer->Begin();
        for (Layer* layer : m_LayerStack)
        {
            layer->OnImGuiRender();
        }
        m_ImGuiLayer->End();
       
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
   
    WindowCloseEvent();
	
}

} // namespace KnightEngine
