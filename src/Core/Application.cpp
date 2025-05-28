#include "Core/Application.hpp"
#include "triangle.h"
#include"vector"
#include "shapes.h"
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
        std::cerr << "SDL Initialization failed!" << std::endl;
        return;
    }
    if (!Init_OpenGL() ) {
        std::cerr << "OPEN_GL Initialization failed!" << std::endl;
        return;
    }
    if (!Init_Imgui()) {
        std::cerr << "IMGUI Initialization failed!" << std::endl;
        return;
    }
    Triangle tri;
    Shapes sh;
    sh.InitLineShader();
    
    tri.Init();
    
    // Main game loop
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

       // tri.Render();
        sh.render();
		
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(m_Window);
    }
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
       std::cerr << "Initializatio failed" << SDL_GetError() << std::endl; return false;
   }
    m_Window = SDL_CreateWindow("KnightEngine", m_width, m_height, SDL_WINDOW_OPENGL);
    if (!m_Window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;  return false;
    }
    return true;
    
}

bool Application::Init_OpenGL()
{
    m_Context = SDL_GL_CreateContext(m_Window);
    if (!m_Context) {
        std::cerr << "OpenGL context creation failed: " << SDL_GetError() << std::endl;
        return false;
    }
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
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
        std::cerr << "Failed to initialize ImGui SDL3 backend!" << std::endl;
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 460")) {
        std::cerr << "Failed to initialize ImGui OpenGL backend!" << std::endl;
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
