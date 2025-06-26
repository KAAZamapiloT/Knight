#pragma once
#include "EngineApi.hpp"
#include "Event/Event.hpp"
#include"Core/Logger.hpp"



class KNIGHT_ENGINE_API KeyPressedEvent : public Event
{
public:
	
	KeyPressedEvent(int keyCode, int repeatCount)
		: m_KeyCode(keyCode), m_RepeatCount(repeatCount) {
	}
	std::string ToString() const override {
		return "KeyPressedEvent: " + std::to_string(m_KeyCode);
	}
	EVENT_CLASS_TYPE(KeyPressed)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryKeyboard | (int)EventCategory::EventCategoryInput)
		void Handle() override {
		// Custom logic for handling key pressed event
	    };
	inline int GetRepeatCount() const { return m_RepeatCount; } ///< Returns the number of times the key has been pressed in quick succession.
	
private:
	int m_RepeatCount = 0; ///< Number of times the key has been pressed in quick succession.
	int m_KeyCode ; ///< The key code of the pressed key.
};


class KNIGHT_ENGINE_API KeyReleasedEvent : public Event
{
public:
	KeyReleasedEvent(int keyCode)
		: m_KeyCode(keyCode) {
	}
	std::string ToString() const override {
		return "KeyReleasedEvent: " + std::to_string(m_KeyCode);
	}
	EVENT_CLASS_TYPE(KeyReleased)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryKeyboard | (int)EventCategory::EventCategoryInput)

		void Handle() override {
		// Custom logic for handling key released event
	};
	inline double GetTimePressed() const { return m_TimePressed; } ///< Returns the time the key was pressed, used for calculating hold duration.
	inline int GetKeyCode() const { return m_KeyCode; } ///< Returns the key code of the released key.
private:
	int m_KeyCode; ///< The key code of the released key.
	double m_TimePressed = 0; ///< The time the key was pressed, used for calculating hold duration.
};
