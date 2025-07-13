#pragma once
#include"EngineApi.hpp"

namespace KnightEngine {

	class KNIGHT_ENGINE_API TimeStamp {
	public:
		TimeStamp(float Time=0.0f) {
			m_Time = Time;
		}
		operator float() { return m_Time; }
		float GetSeconds() const { return m_Time; }
		float GetMiliSeconds() const { return m_Time * 1000.f; }
	private:
		float m_Time;
	};
}