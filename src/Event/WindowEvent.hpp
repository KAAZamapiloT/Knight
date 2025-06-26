#pragma once

#include"EngineApi.hpp"
#include "Event/Event.hpp"
#include"Core/Logger.hpp"

class KNIGHT_ENGINE_API WindowCloseEvent : public Event {
public:
	WindowCloseEvent() {
		// Constructor logic if needed
		KE_TAG_LOG_INFO("WindowEvent", "WindowCloseEvent created");
	}
	void Handle() override {
		// Custom logic for handling window close event
    
	}
	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
private:

};
class KNIGHT_ENGINE_API WindowResizeEvent : public Event {
public:
	WindowResizeEvent(unsigned int width, unsigned int height)
		: m_width(width), m_height(height) {
	}
	void Handle() override {
		// Custom logic for handling window resize event

	}
	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)

	inline unsigned int GetWidth() const { return m_width; }
	inline unsigned int GetHeight() const { return m_height; }

	std::string ToString() const override {
		return "WindowResizeEvent: " + std::to_string(m_width) + ", " + std::to_string(m_height);
	}
private:
	unsigned int m_width, m_height;
};
class KNIGHT_ENGINE_API WindowFocusEvent : public Event {
public:
	void Handle() override {
		// Custom logic for handling window focus event

	}
	
	EVENT_CLASS_TYPE(WindowFocus)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
private:

};
class KNIGHT_ENGINE_API WindowLostFocusEvent : public Event {
public:
	void Handle() override {
		// Custom logic for handling window lost focus event

	}
	EVENT_CLASS_TYPE(WindowLostFocus)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
private:

};
class KNIGHT_ENGINE_API WindowMovedEvent : public Event {

public:
	void Handle() override {
		// Custom logic for handling window moved event

	}
	EVENT_CLASS_TYPE(WindowMoved)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
private:
	int m_x, m_y;
};
class KNIGHT_ENGINE_API WindowMinimizedEvent : public Event {
public:
	void Handle() override {
		// Custom logic for handling window minimized event
	}
	EVENT_CLASS_TYPE(WindowMinimized)
		EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
};
class KNIGHT_ENGINE_API WindowMaximizedEvent : public Event {
public:
	void Handle() override {
		// Custom logic for handling window maximized event
	
	}
	EVENT_CLASS_TYPE(WindowMaximized)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
};


