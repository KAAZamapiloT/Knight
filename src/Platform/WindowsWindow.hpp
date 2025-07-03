#pragma once
#include"Platform/Window.hpp"
#include"glad/glad.h"
#include"SDL3/SDL.h"
#include"KnightEnginepch.h"
namespace KnightEngine
{
	class KNIGHT_ENGINE_API WindowsWindow :public Window
	{

	public:
		struct WindowData {
			int Width, Height;
			std::string Title;
			bool VSync;
			EventCallbackFn EventCallback;
		};
	public:
	//	using EventCallbackFn = std::function<void(Event&)>;
		WindowsWindow(const WindowProps& props);
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		~WindowsWindow();
		void OnUpdate() override;
		//Window Attributes
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		inline std::string GetTitle() const { return m_Data.Title; }
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		EventCallbackFn GetEventCallback() const { return m_Data.EventCallback; }
		SDL_Window* GetNativeWindow() const override { return m_Window; }
		SDL_GLContext GetSDLGLContext() const override { return m_GLContext; }
	private:
		SDL_Window* m_Window = nullptr;
		SDL_GLContext m_GLContext = nullptr;
		void Init(const WindowProps& props);
		void Shutdown();
		
		WindowData m_Data;
	


	public:
		using SDLWindowSizeCallback = std::function<void(SDL_Window*, int, int)>;
		using SDLWindowCloseCallback = std::function<void(SDL_Window*)>;
		using SDLKeyCallback = std::function<void(SDL_Window*, const SDL_Event&, int, int, int, int)>;
		using SDLMouseButtonCallback = std::function<void(SDL_Window*, const SDL_Event&, int, int, int)>;
		using SDLMouseScrollCallback = std::function<void(SDL_Window*, const SDL_Event&, double, double)>;
		using SDLCursorPosCallback = std::function<void(SDL_Window*, double, double)>;
		using KeyTypedCallback = std::function<void(SDL_Window*, unsigned int)>;
		SDLWindowSizeCallback      m_WindowSizeCallback;
		SDLWindowCloseCallback     m_WindowCloseCallback;
		SDLKeyCallback             m_KeyCallback;
		SDLMouseButtonCallback     m_MouseButtonCallback;
		SDLMouseScrollCallback     m_MouseScrollCallback;
		SDLCursorPosCallback       m_CursorPosCallback;
		KeyTypedCallback           m_KeyTypedCallback;
		void SetWindowSizeCallback(SDL_Window* window,SDLWindowSizeCallback cb) { m_WindowSizeCallback = cb; }
		void SetWindowCloseCallback(SDL_Window* window,SDLWindowCloseCallback cb) { m_WindowCloseCallback = cb; }
		void SetKeyCallback(SDL_Window* window,SDLKeyCallback cb) { m_KeyCallback = cb; }
		void SetMouseButtonCallback(SDL_Window* window,SDLMouseButtonCallback cb) { m_MouseButtonCallback = cb; }
		void SetMouseScrolledCallback(SDL_Window* window,SDLMouseScrollCallback cb) { m_MouseScrollCallback = cb; }
		void SetCursorPosCallback(SDL_Window* window,SDLCursorPosCallback cb) { m_CursorPosCallback = cb; }
		void SetKeyTypedCallback(SDL_Window* window, KeyTypedCallback cb) { m_KeyTypedCallback = cb; }
	};

	}


