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
		std::string info = "WindowResizeEvent created with width: " + std::to_string(width) + " and height: " + std::to_string(height);
		KE_TAG_LOG_DEBUG("WindowEvent", info.c_str());
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
	WindowFocusEvent() {
		// Constructor logic if needed
		KE_TAG_LOG_INFO("WindowEvent", "WindowFocusEvent created");
	}
	void Handle() override {
		// Custom logic for handling window focus event

	}
	
	EVENT_CLASS_TYPE(WindowFocus)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
private:

};


class KNIGHT_ENGINE_API WindowLostFocusEvent : public Event {
public:
	WindowLostFocusEvent() {
		// Constructor logic if needed
		KE_TAG_LOG_INFO("WindowEvent", "WindowLostFocusEvent created");
	}
	void Handle() override {
		// Custom logic for handling window lost focus event

	}
	EVENT_CLASS_TYPE(WindowLostFocus)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
private:

};


class KNIGHT_ENGINE_API WindowMovedEvent : public Event {

public:
	WindowMovedEvent(int x, int y)
		: m_x(x), m_y(y) {
		std::string info = "WindowMovedEvent created with x: " + std::to_string(x) + " and y: " + std::to_string(y);
		KE_TAG_LOG_DEBUG("WindowEvent", info.c_str());
	}
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
	WindowMinimizedEvent() {
		// Constructor logic if needed
		KE_TAG_LOG_INFO("WindowEvent", "WindowMinimizedEvent created");
	}
	void Handle() override {
		// Custom logic for handling window minimized event
	}
	EVENT_CLASS_TYPE(WindowMinimized)
		EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
};




class KNIGHT_ENGINE_API WindowMaximizedEvent : public Event {
public:
	WindowMaximizedEvent() {
		// Constructor logic if needed
		KE_TAG_LOG_INFO("WindowEvent", "WindowMaximizedEvent created");
	}
	void Handle() override {
		// Custom logic for handling window maximized event
	
	}
	EVENT_CLASS_TYPE(WindowMaximized)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
};


