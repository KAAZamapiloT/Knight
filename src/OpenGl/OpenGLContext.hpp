#pragma once
#include "Rendering/GraphicsContext.h"
#include "KnightEnginepch.h"
#include "SDL3/SDL.h"
#include"glad/glad.h"
namespace KnightEngine
{
	class KNIGHT_ENGINE_API OpenGLContext :public GraphicsContext
	{
	public:
		OpenGLContext() = default;
		OpenGLContext(SDL_Window* window)
			: m_Window(window) {
			if (!m_Window) {
				KE_TAG_LOG_CRITICAL("OpenGLContext", "SDL_Window is null");
			}
			else {
				KE_TAG_LOG_INFO("OpenGLContext", "OpenGLContext created for window: {}", SDL_GetWindowTitle(m_Window));
			}
		}
		inline SDL_Window* GetWindow() const { return m_Window; }
		inline SDL_GLContext GetSDLGLContext() const { return m_GLContext; }
		~OpenGLContext() = default;
		void Init() override;
		void SwapBuffers() override;
	private:
		SDL_Window* m_Window = nullptr;
		SDL_GLContext m_GLContext = nullptr; ///< The OpenGL context associated with the window.
	};
}

