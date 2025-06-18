#pragma once

#include"EngineApi.hpp"
#include "Event/Event.hpp"
#include"Core/Logger.hpp"

class KNIGHT_ENGINE_API WindowCloseEvent : public Event {
public:
	void Handle() override {
		// Custom logic for handling window close event

	}
	EventType GetType() const override {
		return EventType::WindowClose;
	}
	int GetCategoryFlags() const override {
		return (int)EventCategory::EventCategoryApplication;
	}
	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
private:

};
class KNIGHT_ENGINE_API WindowResizeEvent : public Event {
public:
	void Handle() override {
		// Custom logic for handling window resize event

	}
	EventType GetType() const override {
		return EventType::WindowResize;
	}
	int GetCategoryFlags() const override {
		return (int)EventCategory::EventCategoryApplication;
	}
	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
private:

};
class KNIGHT_ENGINE_API WindowFocusEvent : public Event {
public:
	void Handle() override {
		// Custom logic for handling window focus event

	}
	EventType GetType() const override {
		return EventType::WindowFocus;
	}
	int GetCategoryFlags() const override {
		return (int)EventCategory::EventCategoryApplication;
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
	EventType GetType() const override {
		return EventType::WindowMoved;
	}
	int GetCategoryFlags() const override {
		return (int)EventCategory::EventCategoryApplication;
	}

	EVENT_CLASS_TYPE(WindowMoved)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
private:

};
