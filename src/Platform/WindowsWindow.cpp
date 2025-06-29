#include "WindowsWindow.hpp"
#include "Core/Logger.hpp"
#include"string"
#include"SDL3/SDL.h"
//#include"Platform/Window.hpp"
#include <functional>
#include"Event/WindowEvent.hpp"
#include"Event/KeyEvent.hpp"
#include"Event/MouseEvent.hpp"
#include"Event/ApplicationEvents.hpp"
namespace KnightEngine
{
	static void CheckSDLError(const std::string& context) {
		const char* error = SDL_GetError();
		if (error && *error) {
			KE_TAG_LOG_CRITICAL("SDL Error", "[{}] -> {}", context, error);
			SDL_ClearError();
		}
	}
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

///helper function to clean event callback


	

void KnightEngine::WindowsWindow::OnUpdate()
{
	SDL_Event E;
	
	while (SDL_PollEvent(&E)) {
		if (E.type == SDL_EVENT_QUIT) {
			KE_TAG_LOG_DEBUG("WindowsWindow", "Quit event received for window: {}", m_Data.Title);
			m_WindowCloseCallback(m_Window);
			continue;
		}

		// Dispatch event to your registered callbacks
		switch (E.type) {
		case SDL_EVENT_WINDOW_RESIZED:
		{
			auto window = GetWindowByTitle(SDL_GetWindowTitle(m_Window));
			if (window) {
				int width = E.window.data1;
				int height = E.window.data2;
				// Call your bound resize callback
				// (You will need to store this callback somewhere!)
				
				m_WindowSizeCallback(m_Window, width, height);
			}
			break;
		}

		case SDL_EVENT_KEY_DOWN:
		{
			if (m_KeyCallback)
				m_KeyCallback(m_Window, E, E.key.key, E.key.scancode, SDL_EVENT_KEY_DOWN, E.key.mod);
			
			break;
		}
		case SDL_EVENT_KEY_UP:
		{
			// Similarly dispatch your key callbacks
			if (m_KeyCallback)
				m_KeyCallback(m_Window, E, E.key.key, E.key.scancode, SDL_EVENT_KEY_UP, E.key.mod);
			break;
		}

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		{
			// Dispatch mouse button callback
			m_MouseButtonCallback(m_Window, E, E.button.button, SDL_EVENT_MOUSE_BUTTON_DOWN, E.button.clicks);
			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_UP:
		{
			// Dispatch mouse button callback
			m_MouseButtonCallback(m_Window, E, E.button.button, E.type == SDL_EVENT_MOUSE_BUTTON_DOWN ? SDL_EVENT_MOUSE_BUTTON_DOWN : SDL_EVENT_MOUSE_BUTTON_UP, E.button.clicks);
			break;
		}

		case SDL_EVENT_MOUSE_WHEEL:
		{
			// Dispatch scroll callback
			m_MouseScrollCallback(m_Window,E, E.wheel.x, E.wheel.y);
			break;
		}

		case SDL_EVENT_MOUSE_MOTION:
		{
			// Dispatch mouse move callback
			m_CursorPosCallback(m_Window, E.motion.x, E.motion.y);
			break;
		}

		default:
			break;
		}
		
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
/*
void SetWindowSizeCallback(SDL_Window* m_Window, std::function<void(SDL_Window*, int, int)> callback)
{
	// Store or call the callback later
	// Example call:
	//callback(m_Window, 800, 600);
}
void SetWindowCloseCallback(SDL_Window* m_Window, std::function<void(SDL_Window*)> callback)
{
	// Implement the logic to set a window close callback
	// This could involve SDL event handling or other mechanisms
}

void SetKeyCallback(SDL_Window* m_Window, std::function<void(SDL_Window*,const SDL_Event&e,int Key, int ScanCode,int Action,int Mods)> callback)
{
	// Implement the logic to set a key callback
	// This could involve SDL event handling or other mechanisms
}

void SetMouseButtonCallback(SDL_Window* m_Window, std::function<void(SDL_Window*, const SDL_Event& e, int Button, int Action, int Mods)> callback)
{
	// Implement the logic to set a mouse button callback
	// This could involve SDL event handling or other mechanisms
}
void SetMouseScrolledCallback(SDL_Window* m_Window, std::function<void(SDL_Window*, const SDL_Event& e, double xOffset, double yOffset)> callback)
{
	// Implement the logic to set a mouse scrolled event callback
	// This could involve SDL event handling or other mechanisms
}
void SetCursorPosCallback(SDL_Window* m_Window, std::function<void(SDL_Window*, double x, double y)> callback)
{
	// Implement the logic to set a cursor position callback
	// This could involve SDL event handling or other mechanisms
}*/
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
	CheckSDLError("SDL_CreateWindow");
	// You can attach user data here if needed
	

	m_GLContext = SDL_GL_CreateContext(m_Window);
	if (!m_GLContext) {
		KE_TAG_LOG_CRITICAL("WindowsWindow", "OpenGL context could not be created! SDL_Error: {}", SDL_GetError());
		return;
	}
	CheckSDLError("SDL_GL_CreateContext");
	SDL_GL_MakeCurrent(m_Window, m_GLContext);
	SDL_GL_SetSwapInterval(m_Data.VSync ? 1 : 0);
	SDL_SetWindowTitle(m_Window, m_Data.Title.c_str());
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		KE_TAG_LOG_CRITICAL("WindowsWindow", "Failed to initialize GLAD.");
		return;
	}

	glViewport(0, 0, m_Data.Width, m_Data.Height);

	KE_TAG_LOG_INFO("WindowsWindow", "OpenGL Info:");
	KE_TAG_LOG_INFO("WindowsWindow", "  Vendor:   {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	KE_TAG_LOG_INFO("WindowsWindow", "  Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	KE_TAG_LOG_INFO("WindowsWindow", "  Version:  {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));


	// Set the initial event callback
	SetWindowSizeCallback(m_Window, [](SDL_Window* window, int width, int height) {
		// Your resize logic here
		WindowsWindow* win = GetWindowByTitle(SDL_GetWindowTitle(window));
		WindowData& data = win->m_Data;
		KE_TAG_LOG_DEBUG("WindowsWindow", "Pulled Window With Title {}", data.Title);
		data.Width = width;
		data.Height = height;
		WindowResizeEvent resizeEvent(width, height);
		data.EventCallback(resizeEvent);
		});

	SetWindowCloseCallback(m_Window, [](SDL_Window* window) {
	
		WindowsWindow* win = GetWindowByTitle(SDL_GetWindowTitle(window));
		if (win) {
			WindowCloseEvent closeEvent;
			win->m_Data.EventCallback(closeEvent);
			KE_TAG_LOG_DEBUG("WindowsWindow", "Window close event triggered for {}", win->m_Data.Title);
		}
		
		});

	SetKeyCallback(m_Window, [](SDL_Window* window, const SDL_Event& e, int KeyCode,int	ScanCode,int Action,int Mods) {
		WindowsWindow* win = GetWindowByTitle(SDL_GetWindowTitle(window));
		WindowData& data = win->m_Data;
	
		KE_TAG_LOG_DEBUG("WindowsWindow", "Key event in window {}", data.Title);
		switch (Action) {
		case SDL_EVENT_KEY_DOWN:
		{
			KeyPressedEvent keyPressedEvent(KeyCode, e.key.repeat);
			data.EventCallback(keyPressedEvent);
			break;
		}
		case SDL_EVENT_KEY_UP:
		{
			KeyReleasedEvent keyReleasedEvent(KeyCode);
			data.EventCallback(keyReleasedEvent);
			break;
		}
		default:
			break;
		}
		});

	SetMouseButtonCallback(m_Window, [](SDL_Window*Window, const SDL_Event& e, int Button, int Action, int Mods) {

		WindowsWindow* win = GetWindowByTitle(SDL_GetWindowTitle(Window));
		WindowData& data = win->m_Data;
		KE_TAG_LOG_DEBUG("WindowsWindow", "Mouse button event in window {}", data.Title);
		switch (Action) {

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		{
			MouseButtonPressedEvent mousePressedEvent(Button);
			data.EventCallback(mousePressedEvent);
			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_UP:
		{
			MouseButtonReleasedEvent mouseReleasedEvent(Button);
			data.EventCallback(mouseReleasedEvent);
			break;
		}
		default:
			break;
		}
		});
	SetMouseScrolledCallback(m_Window, [](SDL_Window* window, const SDL_Event& e, double xOffset, double yOffset) {
		WindowsWindow* win = GetWindowByTitle(SDL_GetWindowTitle(window));	
		WindowData& data = win->m_Data;
		MouseScrolledEvent Event((float)xOffset, (float)yOffset);
		data.EventCallback(Event);
		KE_TAG_LOG_INFO("WindowsWindow", "Mouse scrolled by ({}, {}) in window {}", xOffset, yOffset, data.Title);
		});

	SetCursorPosCallback(m_Window, [](SDL_Window* window, double x, double y) {
		WindowsWindow* win = GetWindowByTitle(SDL_GetWindowTitle(window));
		WindowData& data = win->m_Data;
		MouseMovedEvent mouseMovedEvent((float)x, (float)y);
		KE_TAG_LOG_INFO("WindowsWindow", "Mouse moved to ({}, {}) in window {}", x, y, data.Title);
		data.EventCallback(mouseMovedEvent);
		});

}

void KnightEngine::WindowsWindow::Shutdown()
{
	if (m_GLContext) {

		m_GLContext = nullptr;
	}
	if (m_Window) {
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	}
	s_SDLInitialized = false;
	KE_TAG_LOG_INFO("WindowsWindow", "Window {} destroyed", m_Data.Title);
}


