#pragma once
#include "Engine.hpp"
#include "EngineApi.hpp"
#include "Event/Event.hpp"
namespace KnightEngine
{
	class KNIGHT_ENGINE_API KeyboardEvent:public Event
	{
	public:
		
	private:
		uint32_t m_KeyCode = 0;
		bool m_Repeat = false;
		bool IsHold = false;
		float m_StartTime;
		float m_EndTime;
	};
}
