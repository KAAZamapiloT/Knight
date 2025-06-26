#pragma once
#include"Platform/Window.hpp"
#include"glad/glad.h"
#include"SDL3/SDL.h"
#include"Engine.hpp"
namespace KnightEngine
{
	class KNIGHT_ENGINE_API WindowsWindow :public Window
	{
	public:
	//	using EventCallbackFn = std::function<void(Event&)>;
		WindowsWindow(const WindowProps& props);
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		void OnUpdate() override;
		//Window Attributes
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
	private:
		SDL_Window* m_Window = nullptr;
		SDL_GLContext m_GLContext = nullptr;
		void Init(const WindowProps& props);
		void Shutdown();
		struct WindowData {
			int Width, Height;
			std::string Title;
			bool VSync;
			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};

	}


