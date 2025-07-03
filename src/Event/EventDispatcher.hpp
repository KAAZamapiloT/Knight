#pragma once
#include "EngineApi.hpp"
#include "Core/Logger.hpp"
#include"KnightEnginepch.h"
#include "Event/Event.hpp"
class KNIGHT_ENGINE_API EventDispatcher
{

private:

	template<typename T>
	using Eventfn = std::function<bool(T&)>;
public:
	/**
	 * @brief Constructs an EventDispatcher for a specific event type.
	 * @param event Reference to the event to be dispatched.
	 */
	EventDispatcher(Event& event) : m_Event(event) {}
	/**
	 * @brief Dispatches the event to the specified handler function.
	 * @tparam T The type of the event handler function.
	 * @param func The handler function to process the event.
	 * @return True if the event was handled, false otherwise.
	 */

	
/*	template<typename T>
	bool Dispatch(const T& func) {
		if (!m_Event.IsHandled() && m_Event.GetType() == T::GetStaticType()) {
			m_Event.Handle();
			return true;
		}
		return false;
	}
	*/
	template<typename T>
	bool Dispatch(Eventfn <T> func) {
		if (m_Event.GetType() == T::GetStaticType()) {
			m_Event.SetHandled(func(static_cast<T&>(m_Event)));
			//m_Event.b_IsHandled = func(*(T*)&m_Event); ///< Mark the event as handled.
			return true;
		}
		return false;
	}

private:
	Event& m_Event; ///< Reference to the event being dispatched.
};


inline std::ostream& operator<<(std::ostream& os, const Event& e) {
	return os << e.ToString();
}