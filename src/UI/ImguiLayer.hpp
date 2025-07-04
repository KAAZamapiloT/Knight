#pragma once
#include "EngineApi.hpp"
#include "KnightEnginepch.h"
#include "Core/Logger.hpp"
#include"imgui.h"


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
		virtual void OnImGuiRender() override; ///< Render ImGui interface
		void Begin();
		void End();
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
		bool showDemo = true;
		float m_time = 0.0f;
	};
}

