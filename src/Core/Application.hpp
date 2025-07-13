#pragma once
#include<iostream>
#include "EngineApi.hpp"
#include"Platform/Window.hpp"
#include"Graphics/Renderer.hpp"
#include"Event/WindowEvent.hpp"
#include"Event/EventDispatcher.hpp"
#include"Layer/LayerStack.hpp"
#include"input/InputManager.h"
#include"UI/ImguiLayer.hpp"
#include"shaderComp.h"
#include"Graphics/VertexBuffer.hpp"
#include"Graphics/VertexArray.hpp"
#include"Graphics/Renderer.hpp"
#include"Graphics/Camera.hpp"
#include"Core/Time.hpp"
namespace KnightEngine {

    class KNIGHT_ENGINE_API Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();
        bool OnWindowClose(WindowCloseEvent& E);
        bool OnwindowResize(WindowResizeEvent& E);
        void OnEvent(Event& E);
        void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		inline Window& GetWindow() { return *M_Window; }
		static inline Application* GetInstance() { return sInstance; }
    protected:
      
        virtual  void OnShutdown();
    private:
        int m_width = 1240;
        int m_height = 720;
	


     
        void Shutdown();
        bool m_Running = true;
        const char* t = "TestWindow";
		Knight::Renderer* m_Renderer = nullptr;
		std::unique_ptr<Window> M_Window = nullptr;
		LayerStack m_LayerStack; ///< The stack of layers in the application.
		ImguiLayer* m_ImGuiLayer; ///< The ImGui layer for rendering the UI.
        static Application* sInstance; ///< Singleton instance of the application.

        float m_LastTime=0.0f;
        
    };

    // To be defined in client
}// namespace KnightEngine
