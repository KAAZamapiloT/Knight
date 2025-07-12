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
		std::shared_ptr<VertexArray> m_VertexArray; ///< Vertex array for rendering.
		std::shared_ptr<ShaderComp> m_Shader; ///< The shader used for rendering.
        std::shared_ptr<VertexArray> m_SquareVA;
        std::shared_ptr<ShaderComp> m_Shader2;


     
        void Shutdown();
        bool m_Running = true;
        const char* t = "TestWindow";
		Knight::Renderer* m_Renderer = nullptr;
		std::unique_ptr<Window> M_Window = nullptr;
        Knight::Camera M_Camera;
		LayerStack m_LayerStack; ///< The stack of layers in the application.
		ImguiLayer* m_ImGuiLayer; ///< The ImGui layer for rendering the UI.
        static Application* sInstance; ///< Singleton instance of the application.

        
    };

    // To be defined in client
}// namespace KnightEngine
