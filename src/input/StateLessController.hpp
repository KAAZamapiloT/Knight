#pragma once
#include"KnightEnginepch.h"
#include"EngineApi.hpp"
#include "Graphics/Camera.hpp"
#include"Core/Time.hpp"
#include"Event/KeyEvent.hpp"
#include"Event/MouseEvent.hpp"
#include"Event/WindowEvent.hpp"
#include"Event/ApplicationEvents.hpp"

namespace Knight {
	class KNIGHT_ENGINE_API StateLessController
	{
	public:
		void OnUpdate(Camera& Cam, KnightEngine::TimeStamp);
		void OnEvent(Camera& Cam, Event& E);
	};

}

