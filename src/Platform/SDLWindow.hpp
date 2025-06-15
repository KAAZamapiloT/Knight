#pragma once
#include "EngineApi.hpp"
#include <memory>
#include "Core/Window.hpp"
#include "SDL3/SDL.h"
namespace KnightEngine {
	class KNIGHT_ENGINE_API SDLWindow : public  Window
	{
	public:
		bool PollEvents() override;
		void SwapBuffers() override;
		void* GetNativeWindow() override;
		int GetWidth() const override { return m_Width; }
		int GetHeight() const override { return m_Height; }
		void Shutdown() override;
		SDLWindow(int width, int height, const char* title);
		~SDLWindow();
		
	private:
		SDL_Window* m_Window = nullptr;
		SDL_GLContext m_GLContext = nullptr;
		int m_Width, m_Height;
		
	};
}
