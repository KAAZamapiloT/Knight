#pragma once
#include "EngineApi.hpp"
#include "Event/Event.hpp"
#include"KnightEnginepch.h"



class KNIGHT_ENGINE_API KeyPressedEvent : public Event
{
public:
	
	KeyPressedEvent(int keyCode, int repeatCount)
		: m_KeyCode(keyCode), m_RepeatCount(repeatCount) {
	}
	KeyPressedEvent(int keyCode,int repeatCount, int mod)
		: m_KeyCode(keyCode), m_RepeatCount(repeatCount), m_Mod(mod) {
	}
	KeyPressedEvent(int keyCode, int scanCode,  int mod ,int repeatCount)
		: m_KeyCode(keyCode), m_ScanCode(scanCode), m_RepeatCount(repeatCount), m_Mod(mod) {
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
	inline int GetKeyCode() const { return m_KeyCode; } ///< Returns the key code of the pressed key.
	inline int GetScanCode() const { return m_ScanCode; } ///< Returns the scan code of the pressed key, useful for low-level input handling.	
	inline int GetMod() const { return m_Mod; }
private:
	int m_RepeatCount = 0; ///< Number of times the key has been pressed in quick succession.
	int m_KeyCode=0 ; ///< The key code of the pressed key.
	int m_Mod=0;
	int m_ScanCode = 0; ///< The scan code of the pressed key, useful for low-level input handling.
};


class KNIGHT_ENGINE_API KeyReleasedEvent : public Event
{
public:
	KeyReleasedEvent(int keyCode)
		: m_KeyCode(keyCode) {
	}
	KeyReleasedEvent(int keyCode, int mod)
		: m_KeyCode(keyCode),  m_Mod(mod) {
	}
	KeyReleasedEvent(int keyCode, int scanCode, int mod)
		: m_KeyCode(keyCode),m_Mod(mod), m_ScanCode(scanCode) {
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
	inline int GetScanCode() const { return m_ScanCode; } ///< Returns the scan code of the released key, useful for low-level input handling.
	inline int GetMod() const { return m_Mod; } ///< Returns the modifier keys (like Shift, Ctrl) that were pressed along with the key.
private:
	int m_KeyCode=0; ///< The key code of the released key.
	double m_TimePressed = 0; ///< The time the key was pressed, used for calculating hold duration.
	int m_Mod = 0;
	int m_ScanCode = 0;///< Modifier keys (like Shift, Ctrl) that were pressed along with the key.
};
class KNIGHT_ENGINE_API KeyTypedEvent : public Event
{
public:
	KeyTypedEvent(int keyCode)
		: m_Character(keyCode) {
	}

	std::string ToString() const override {
		return "KeyTypedEvent: " + std::to_string(m_Character);
	}
	EVENT_CLASS_TYPE(KeyTyped)
		EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryKeyboard | (int)EventCategory::EventCategoryInput)
		void Handle() override {
		// Custom logic for handling key typed event
	};
	inline unsigned int GetCharacterCode() const { return m_Character; } ///< Returns the character code of the typed key, useful for text input.
private:
	unsigned int m_Character = 0;
};




