#pragma once
#include"EngineApi.hpp"
#include "Event/Event.hpp"
#include"Core/Logger.hpp"

class KNIGHT_ENGINE_API AppTickEvent : public Event {
public:
	void Handle() override {
		// Custom logic for handling application tick event
	}
	EventType GetType() const override {
		return EventType::AppTick;
	}
	int GetCategoryFlags() const override {
		return (int)EventCategory::EventCategoryApplication;
	}
	    EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
private:
};
class KNIGHT_ENGINE_API AppUpdateEvent : public Event {
public:
	void Handle() override {
		// Custom logic for handling application update event
	}
	EventType GetType() const override {
		return EventType::AppUpdate;
	}
	int GetCategoryFlags() const override {
		return (int)EventCategory::EventCategoryApplication;
	}
	EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
};
class KNIGHT_ENGINE_API AppRenderEvent : public Event {
public:
	void Handle() override {
		// Custom logic for handling application render event
	}
	EventType GetType() const override {
		return EventType::AppRender;
	}
	int GetCategoryFlags() const override {
		return (int)EventCategory::EventCategoryApplication;
	}
	EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
};


