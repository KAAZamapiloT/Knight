#pragma once
#include "EngineApi.hpp"
#include "KnightEnginepch.h"
#include "Core/Logger.hpp"
#include"imgui.h"
#include "imgui_impl_opengl3.h"
#include"imgui_impl_sdl3.h"

#include "Layer/Layer.hpp"
#include"KnightEnginepch.h"
#include "Event/MouseEvent.hpp"
#include "Event/KeyEvent.hpp"
#include "Event/WindowEvent.hpp"
#include "Event/EventDispatcher.hpp"
namespace KnightEngine
{
	class KNIGHT_ENGINE_API ImguiLayer:public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
		ImGuiKey SDL_TO_ImGuiKey(int KeyCode, int ScanCode);
		int SDL_MOUSE_TO_IMGUI(int sdlButton);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnWindowResizeEvent(WindowResizeEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		

	private:
		
		float m_time = 0.0f;
	};
}

