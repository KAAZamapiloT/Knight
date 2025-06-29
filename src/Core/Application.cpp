#include "Core/Application.hpp"
#include "triangle.h"
#include"vector"
#include "shapes.h"
#include "Core/Logger.hpp"
#include"Graphics/Renderer.hpp"
#include"utils/Math.hpp"

namespace KnightEngine {
#define BIND_EVENT_FN(X) std::bind(&X, this, std::placeholders::_1)
// Implementation of Application class
Application::Application()
{
    // Initialize core systems here
	KE_LOG_INFO("Application is starting");
	M_Window = std::unique_ptr<Window>(Window::Create(WindowProps("KnightEngine", 1240, 720)));
    M_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
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
}
bool Application::OnWindowClose(WindowCloseEvent& E)
{
    m_Running = false;
    return true;
}

bool Application::OnInit_SDL()
{
    return false;
}

bool Application::OnInit_OpenGL()
{
    return false;
}

bool Application::OnInit_Imgui()
{
	/*
	// Initialize ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	// Setup Dear ImGui style
	// You can customize the style here if needed
	ImGui::StyleColorsDark();

    ImGui::Begin("Knight Engine UI");
   ImGui::Text("CAN I ENTER DIFFRENT TEXT");
    ImGui::End();
    return true;
    */
    return true;
}

void Application::OnShutdown()
{
     M_Window.reset();
    
}

bool Application::Init_SDL()
{
  
    return true;
}

bool Application::Init_OpenGL()
{
    /*m_Context = SDL_GL_CreateContext(m_Window);
    if (!m_Context) {
       // std::cerr << "OpenGL context creation failed: " << SDL_GetError() << std::endl;
		KE_LOG_CRITICAL("OpenGL context creation failed: " , std::string(SDL_GetError()));
        return false;
    }
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
      //  std::cerr << "Failed to initialize GLAD" << std::endl;
		KE_LOG_CRITICAL("Failed to initialize GLAD");
        return false;
    }*/
    return true;
}

bool Application::Init_Imgui()
{
  /*  IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Backend bindings
    if (!ImGui_ImplSDL3_InitForOpenGL(, m_Context)) {
       // std::cerr << "Failed to initialize ImGui SDL3 backend!" << std::endl;
		KE_LOG_CRITICAL("Failed to initialize ImGui SDL3 backend!");
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 460")) {
      //  std::cerr << "Failed to initialize ImGui OpenGL backend!" << std::endl;
		KE_LOG_CRITICAL("Failed to initialize ImGui OpenGL backend!");
        return false;
    }*/
    return true;
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
