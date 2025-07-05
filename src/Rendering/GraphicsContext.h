#pragma once
#include"EngineApi.hpp"
namespace KnightEngine {
	class KNIGHT_ENGINE_API GraphicsContext
	{
	public:
		virtual void Init()=0;
		virtual void SwapBuffers() = 0;
	};
}


