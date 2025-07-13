#pragma once

#include "EngineApi.hpp"
#include"KnightEnginepch.h"

namespace KnightEngine {

	class KNIGHT_ENGINE_API InputManager
	{
	public:
		static bool IsKeyPressed(int button, int mod) { return GetInstance()->IsKeyPressedImpl(button,mod); }
		static bool IsMouseButtonPressed(int button) { return GetInstance()->IsMouseButtonPressedImpl(button); }
		static float GetMouseX()  { return GetInstance()->GetMouseXImpl(); }
		static  float GetMouseY()  { return GetInstance()->GetMouseYImpl(); }
		static std::pair<float, float> GetMousePosition()  {
			return { GetInstance()->GetMouseXImpl(), GetInstance()->GetMouseYImpl()};
		}
		virtual ~InputManager() = default;
	protected:
		virtual bool IsKeyPressedImpl(int button, int mod) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static InputManager* s_Instance;
		static InputManager* GetInstance();
	};

}


