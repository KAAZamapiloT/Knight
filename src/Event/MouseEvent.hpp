#pragma once
#include"EngineApi.hpp"
#include"Event/Event.hpp"
namespace KnightEngine {
	class KNIGHT_ENGINE_API MouseEvent : public Event
	{
	public:


	private:
		uint32_t m_Keycode = 0;
		bool m_IsRepeated = false;
		bool m_IsHold = false;
		float m_StartTime = 0.0f;
		float m_EndTime = 0.0f;
		
	};
}

