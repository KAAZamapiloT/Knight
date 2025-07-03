#pragma once
#include "KnightEnginepch.h"
#include "EngineApi.hpp"
#include"input/InputManager.h"
#include "SDL3/SDL.h"
namespace KnightEngine {
	class KNIGHT_ENGINE_API WindowsInput :public InputManager
	{
	protected:
		virtual bool IsKeyPressedImpl(int button, int mod) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;

		virtual bool IsMouseButtonPressedImpl_WithPosition(int button, float* x, float* y) ;
		virtual bool IsLeftMouseButtonPressed();
		virtual bool IsRightMouseButtonPressed() ;
		virtual bool IsMiddleMouseButtonPressed() ;

		virtual float GetMouseXImpl() override { 
			float x, y; SDL_GetMouseState(&x, &y); return x;
		};
		virtual float GetMouseYImpl() override {
			float x, y; SDL_GetMouseState(&x, &y); return y;
		};

		SDL_Keymod* Knight_TO_SDL_MOD(int mod);
	};
}


