#include "Platform/SDLWindow.hpp"
#include "glad/glad.h"
#include <SDL3/SDL_opengl.h>
#include "Core/Logger.hpp"
#include <iostream>
namespace KnightEngine {
	bool SDLWindow::PollEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if(event.type== SDL_EVENT_QUIT)
			  return false;
		}
		return true;
	}

	void SDLWindow::SwapBuffers()
	{
		SDL_GL_SwapWindow(m_Window);
	}

	void* SDLWindow::GetNativeWindow()
	{
		return static_cast<void*>(m_Window);
	}

	void SDLWindow::Shutdown()
	{
		SDL_GL_MakeCurrent(nullptr, nullptr);

		if (m_GLContext) {
			SDL_GL_DestroyContext(m_GLContext);
			m_GLContext = nullptr;
		}

		if (m_Window) {
			SDL_DestroyWindow(m_Window);
			m_Window = nullptr;
		}

	}

	SDLWindow::SDLWindow(int width, int height, const char* title)
		: m_Width(width), m_Height(height)
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			//std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
			KE_TAG_LOG_CRITICAL("SDLWindow", "SDL_Init failed: {}", SDL_GetError());
		}
		KE_TAG_LOG_DEBUG("SDLWindow", "SDL_Init successful");
		// SDL3: Set OpenGL context version attributes
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		m_Window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (!m_Window) {
			//std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
			KE_TAG_LOG_CRITICAL("SDLWindow", "SDL_CreateWindow failed: {}", SDL_GetError());
		}
		KE_TAG_LOG_INFO("SDLWindow", "Created SDLWindow with title: {}", title);
		m_GLContext = SDL_GL_CreateContext(m_Window);
		if (!m_GLContext) {
			//std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << std::endl;
			KE_TAG_LOG_CRITICAL("SDLWindow", "SDL_GL_CreateContext failed: {}", SDL_GetError());
		}
		KE_TAG_LOG_DEBUG("SDLWindow", "Created OpenGL context for SDLWindow");
		// Load OpenGL functions via GLAD
		if (!gladLoadGL()) {
			//std::cerr << "Failed to initialize OpenGL context." << std::endl;
			KE_TAG_LOG_CRITICAL("SDLWindow", "Failed to initialize OpenGL context.");
		}
		KE_TAG_LOG_INFO("SDLWindow", "OpenGL context initialized with GLAD");
		SDL_GL_MakeCurrent(m_Window, m_GLContext);
		KE_TAG_LOG_INFO("SDLWindow", "Created SDLWindow with OpenGL context");
	}

	SDLWindow::~SDLWindow() {
		KE_TAG_LOG_INFO("SDLWindow", "Destroying SDLWindow");
		Shutdown();
	}

	
}
