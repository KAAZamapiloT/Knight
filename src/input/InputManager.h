#pragma once

#include "EngineApi.hpp"
#include"KnightEnginepch.h"

namespace KnightEngine {

	class KNIGHT_ENGINE_API InputManager
	{
	public:
		static bool IsKeyPressed(int button, int mod) { return s_Instance->IsKeyPressedImpl(button,mod); }
		static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline float GetMouseX() const { return s_Instance->GetMouseXImpl(); }
		inline float GetMouseY() const { return s_Instance->GetMouseYImpl(); }
		inline std::pair<float, float> GetMousePosition() const {
			return { s_Instance->GetMouseXImpl(), s_Instance->GetMouseYImpl()};
		}
	protected:
		virtual bool IsKeyPressedImpl(int button, int mod) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static InputManager* s_Instance;
	};

}


