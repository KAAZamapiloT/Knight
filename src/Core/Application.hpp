#pragma once
#include <SDL3/SDL.h>
#include"glad/glad.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include"imgui_impl_sdl3.h"
#include<iostream>
#include "EngineApi.hpp"

#include"Graphics/Renderer.hpp"
namespace KnightEngine {

    class KNIGHT_ENGINE_API Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();
        bool OnWindowResize();
    protected:
        virtual  bool OnInit_SDL();
        virtual  bool OnInit_OpenGL();
        virtual  bool OnInit_Imgui();
        virtual  void OnShutdown();
    private:
        int m_width = 1240;
        int m_height = 720;
        bool Init_SDL();
        bool Init_OpenGL();
        bool Init_Imgui();
        void Shutdown();
        bool m_Running = true;
        SDL_Window* m_Window = nullptr;
        SDL_GLContext m_Context = nullptr;
        const char* t = "TestWindow";
		Knight::Renderer* m_Renderer = nullptr;
    };

    // To be defined in client
}// namespace KnightEngine
