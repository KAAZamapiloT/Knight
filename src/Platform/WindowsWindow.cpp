#include "WindowsWindow.hpp"
#include "Core/Logger.hpp"
#include"string"
#include"SDL3/SDL.h"
//#include"Platform/Window.hpp"

namespace KnightEngine
{
    static bool s_SDLInitialized = false;
	static std::unordered_map<std::string, WindowsWindow*> s_TitleMap;

	WindowsWindow* GetWindowByTitle(const std::string& title)
	{
		auto it = s_TitleMap.find(title);
		if (it != s_TitleMap.end()) {
			return it->second;
		}
		return nullptr;
	}
	void RegisterByTitle(const std::string& title, WindowsWindow* window)
	{
		s_TitleMap[title] = window;
	}
	void UnRegisterByTitle(const std::string& title)
	{
		s_TitleMap.erase(title);
	}
	
}

KnightEngine::Window* KnightEngine::Window::Create(const WindowProps& props)
{
	return new KnightEngine::WindowsWindow(props);
}

KnightEngine::WindowsWindow::WindowsWindow(const WindowProps& props)
{
	Init(props);
	RegisterByTitle(m_Data.Title, this);
	KE_TAG_LOG_INFO("WindowsWindow", "Window created: {} ({}x{})", m_Data.Title, m_Data.Width, m_Data.Height);
}

KnightEngine::WindowsWindow::~WindowsWindow()
{
	Shutdown();
	UnRegisterByTitle(m_Data.Title);
}

void KnightEngine::WindowsWindow::OnUpdate()
{
	SDL_Event E;
	SDL_PollEvent(&E);
	// HERE DISPACH EVENT IF ITS RECORDED
	if (E.type == SDL_EVENT_QUIT) {
		return;
	}
	SDL_GL_SwapWindow(m_Window);
}

void KnightEngine::WindowsWindow::SetVSync(bool enabled)
{
	m_Data.VSync = enabled;
	SDL_GL_SetSwapInterval(m_Data.VSync ? 1 : 0);
	KE_TAG_LOG_INFO("WindowsWindow", "VSync is now {}", m_Data.VSync ? "enabled" : "disabled");
}

bool KnightEngine::WindowsWindow::IsVSync() const
{
	return m_Data.VSync;
}

void KnightEngine::WindowsWindow::Init(const WindowProps& props)
{
	m_Data.Title = props.Title;
	m_Data.Width = props.Width;
	m_Data.Height = props.Height;
	m_Data.VSync = props.VSync;

	if (!s_SDLInitialized) {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			KE_TAG_LOG_CRITICAL("WindowsWindow", "SDL could not initialize! SDL_Error: {}", SDL_GetError());
			return;
		}
		s_SDLInitialized = true;
	}

	// Must be before window/context creation
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	KE_TAG_LOG_INFO("WindowsWindow", "Creating window: {} ({}x{})", m_Data.Title, m_Data.Width, m_Data.Height);

	m_Window = SDL_CreateWindow(
		m_Data.Title.c_str(),
		m_Data.Width,
		m_Data.Height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);
	SetVSync(true);
	if (!m_Window) {
		KE_TAG_LOG_CRITICAL("WindowsWindow", "Window could not be created! SDL_Error: {}", SDL_GetError());
		return;
	}

	// You can attach user data here if needed
	

	m_GLContext = SDL_GL_CreateContext(m_Window);
	if (!m_GLContext) {
		KE_TAG_LOG_CRITICAL("WindowsWindow", "OpenGL context could not be created! SDL_Error: {}", SDL_GetError());
		return;
	}

	SDL_GL_MakeCurrent(m_Window, m_GLContext);
	SDL_GL_SetSwapInterval(m_Data.VSync ? 1 : 0);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		KE_TAG_LOG_CRITICAL("WindowsWindow", "Failed to initialize GLAD.");
		return;
	}

	glViewport(0, 0, m_Data.Width, m_Data.Height);

	KE_TAG_LOG_INFO("WindowsWindow", "OpenGL Info:");
	KE_TAG_LOG_INFO("WindowsWindow", "  Vendor:   {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	KE_TAG_LOG_INFO("WindowsWindow", "  Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	KE_TAG_LOG_INFO("WindowsWindow", "  Version:  {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    
}

void KnightEngine::WindowsWindow::Shutdown()
{
}


