#pragma once
#include"EngineApi.hpp"
#include"Event/Event.hpp"

namespace KnightEngine
{

	class KNIGHT_ENGINE_API EventDispathcer
	{
	public:
		EventDispathcer(Event& event)
			: m_Event(event) {
			
		}
		template<typename T, typename F>
		bool Dispatch(F func)
		{
			if (m_Event.GetType() == T::GetStaticType())
			{
				func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
		template<typename T>
		bool Dispatch()
		{
			return Dispatch<T>([](T&) {});
		}
		
	private:
		Event& m_Event;
	};
}
