#pragma once
#include<iostream>
#include "EngineApi.hpp"
#include"Platform/Window.hpp"
#include"Graphics/Renderer.hpp"
#include"Event/WindowEvent.hpp"
#include"Event/EventDispatcher.hpp"
#include"Layer/LayerStack.hpp"
#include"UI/ImguiLayer.hpp"
#include"Core/Time.hpp"
#include"Core/Core.h"

// Forward declarations
namespace Knight {
	class Renderer;
}
namespace KnightEngine {
	class Layer;
}

namespace KnightEngine {

	class KNIGHT_ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *M_Window; }
		static inline Application* GetInstance() { return sInstance; }

		// Returns a reference to the single, static renderer instance.
		static Knight::Renderer& GetRenderer() { return m_Renderer; }

	protected:
		virtual void OnShutdown();

	private:
		bool OnWindowClose(WindowCloseEvent& E);
		bool OnwindowResize(WindowResizeEvent& E);
		void Shutdown();

		int m_width = 1240;
		int m_height = 720;
		bool m_Running = true;

		Knight::Scope<Window> M_Window;
		LayerStack m_LayerStack;
		ImguiLayer* m_ImGuiLayer;
		float m_LastTime = 0.0f;

		static Application* sInstance;
		// The Application class now owns the single, static instance of the Renderer.
		static Knight::Renderer m_Renderer;
	};

}
