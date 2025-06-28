#pragma once
#include "EngineApi.hpp"
#include "Event/Event.hpp"
class KNIGHT_ENGINE_API MouseMovedEvent :public Event
{
public:
	MouseMovedEvent(float x, float y)
		: m_MouseX(x), m_MouseY(y) {

	}
	void Handle() override {
		// Custom logic for handling mouse moved event can be added here.
	}
	inline float GetX() const { return m_MouseX; } ///< Returns the X coordinate of the mouse.
	inline float GetY() const { return m_MouseY; } ///< Returns the Y coordinate of the mouse.
	std::string ToString() const override {
		return "MouseMovedEvent: (" + std::to_string(m_MouseX) + ", " + std::to_string(m_MouseY) + ")";
	}
	EVENT_CLASS_TYPE(MouseMoved) ///< Returns the static type of the event.
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryMouse | (int)EventCategory::EventCategoryInput)

private:
	float m_MouseX, m_MouseY; ///< Mouse X and Y coordinates.
};

class KNIGHT_ENGINE_API MouseButtonPressedEvent : public Event
{
public:

	MouseButtonPressedEvent(int button)
		: m_Button(button) {
	}
	inline int GetButton() const { return m_Button; } ///< Returns the mouse button that was pressed.
	std::string ToString() const override {
		return "MouseButtonPressedEvent: " + std::to_string(m_Button);
	}
	EVENT_CLASS_TYPE(MouseButtonPressed) ///< Returns the static type of the event.
		EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryMouseButton | (int)EventCategory::EventCategoryInput)

		void Handle() override {
	}

private:
	int m_Button; ///< The mouse button that was pressed.
};

class KNIGHT_ENGINE_API MouseButtonReleasedEvent : public Event
{
public:
	MouseButtonReleasedEvent(int button)
		: m_Button(button) {
	}
	inline int GetButton() const { return m_Button; } ///< Returns the mouse button that was released.
	std::string ToString() const override {
		return "MouseButtonReleasedEvent: " + std::to_string(m_Button);
	}
	EVENT_CLASS_TYPE(MouseButtonReleased) ///< Returns the static type of the event.
		EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryMouseButton | (int)EventCategory::EventCategoryInput)
		void Handle() override {
	}
	inline double GetHoldTime() const { return HoldTime; } ///< Returns the time the button was held down, used for calculating hold duration.
private:
	int m_Button; ///< The mouse button that was released.
	double HoldTime = 0; ///< The time the button was held down, used for calculating hold duration.
};

class KNIGHT_ENGINE_API MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(float xOffset, float yOffset)
		: m_XOffset(xOffset), m_YOffset(yOffset) {
	}
	inline float GetXOffset() const { return m_XOffset; } ///< Returns the horizontal scroll offset.
	inline float GetYOffset() const { return m_YOffset; } ///< Returns the vertical scroll offset.
	std::string ToString() const override {
		return "MouseScrolledEvent: (" + std::to_string(m_XOffset) + ", " + std::to_string(m_YOffset) + ")";
	}
	EVENT_CLASS_TYPE(MouseScrolled) ///< Returns the static type of the event.
		EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryMouse | (int)EventCategory::EventCategoryInput)
		void Handle() override {}
private:
	float m_XOffset, m_YOffset; ///< Horizontal and vertical scroll offsets.

};

