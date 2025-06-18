#pragma once
#include"EngineApi.hpp"
#include "Event/Event.hpp"
#include"Core/Logger.hpp"

class KNIGHT_ENGINE_API AppTickEvent : public Event {
public:
	void Handle() override {
		// Custom logic for handling application tick event
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
	EVENT_CLASS_TYPE(AppUpdate)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
};
class KNIGHT_ENGINE_API AppRenderEvent : public Event {
public:
	void Handle() override {
		// Custom logic for handling application render event
	}
	EVENT_CLASS_TYPE(AppRender)
	EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApplication)
};


