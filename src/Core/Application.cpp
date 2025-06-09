#include "Core/Application.hpp"
#include "triangle.h"
#include"vector"
#include "shapes.h"
#include "Core/Logger.hpp"
#include"Graphics/Renderer.hpp"
#include"utils/Math.hpp"
namespace KnightEngine {

// Implementation of Application class
Application::Application()
{
    // Initialize core systems here
}

Application::~Application()
{
    // Cleanup resources here
}

void Application::Run()
{
    if (!Init_SDL()) {
      //  std::cerr << "SDL Initialization failed!" << std::endl;
		KE_LOG_CRITICAL("SDL Initialization failed!");
        return;
    }
    if (!Init_OpenGL() ) {
      //  std::cerr << "OPEN_GL Initialization failed!" << std::endl;
		KE_LOG_CRITICAL("OPEN_GL Initialization failed!");
        return;
    }
    if (!Init_Imgui()) {
       // std::cerr << "IMGUI Initialization failed!" << std::endl;
		KE_LOG_CRITICAL("IMGUI Initialization failed!");
        return;
    }
    
    Triangle tri;
    Shapes sh;
	Knight::Renderer R;
    Knight::RenderCommand rc;

    float frequency = 0.1f;
	float f = 0.0f;
    float blue = glm::sin(f * frequency);
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
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) m_Running = false;
            ImGui_ImplSDL3_ProcessEvent(&e);
        }
        
        // ImGui frame start
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // Game logic & UI
      //  OnUpdate();
       // OnRenderUI();
        OnInit_Imgui();
        // Rendering
        ImGui::Render();
        glViewport(0, 0, 1280, 720);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        blue = glm::sin(f * frequency);
        blue = (blue + 1.0f) * 0.5f;
        
       
		R.BeginFrame();
       // R.SumbitCommandBuffer();
		R.EndFrame();
        
		rc.ClearColor(0.1f, blue, 0.1f, 1.0f);
		
		f = f + 0.01f;
        tri.Render();
        sh.render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(m_Window);
    }
	KE_LOG_CRITICAL("Application is shutting down");
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
}

void Application::OnShutdown()
{
}

bool Application::Init_SDL()
{
   bool b= SDL_Init(SDL_INIT_VIDEO);
   if (!b) {
      // std::cerr << "Initializatio failed" << SDL_GetError() << std::endl; return false;
	   KE_LOG_CRITICAL("Initialization failed: " , std::string(SDL_GetError()));
	   return false;
   }
    m_Window = SDL_CreateWindow("KnightEngine", m_width, m_height, SDL_WINDOW_OPENGL);
    if (!m_Window) {
      //  std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;  return false;
		KE_LOG_CRITICAL("Window creation failed: " , std::string(SDL_GetError()));
		return false;
    }
    return true;
    
}

bool Application::Init_OpenGL()
{
    m_Context = SDL_GL_CreateContext(m_Window);
    if (!m_Context) {
       // std::cerr << "OpenGL context creation failed: " << SDL_GetError() << std::endl;
		KE_LOG_CRITICAL("OpenGL context creation failed: " , std::string(SDL_GetError()));
        return false;
    }
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
      //  std::cerr << "Failed to initialize GLAD" << std::endl;
		KE_LOG_CRITICAL("Failed to initialize GLAD");
        return false;
    }
    return true;
}

bool Application::Init_Imgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Backend bindings
    if (!ImGui_ImplSDL3_InitForOpenGL(m_Window, m_Context)) {
       // std::cerr << "Failed to initialize ImGui SDL3 backend!" << std::endl;
		KE_LOG_CRITICAL("Failed to initialize ImGui SDL3 backend!");
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 460")) {
      //  std::cerr << "Failed to initialize ImGui OpenGL backend!" << std::endl;
		KE_LOG_CRITICAL("Failed to initialize ImGui OpenGL backend!");
        return false;
    }
    return true;
}

void Application::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();


    SDL_GL_DestroyContext(m_Context);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

} // namespace KnightEngine
