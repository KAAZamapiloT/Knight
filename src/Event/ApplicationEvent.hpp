#pragma once
#include "Engine.hpp"
#include "EngineApi.hpp"
#include"Event/Event.hpp"
namespace KnightEngine
{
	class ApplicationEvent : public Event
	{
	public:
		//void OnApplicationTick();
		//void OnApplicationUpdate();
		//void OnApplicationRender();
	private:
		Type m_Type = Type::ApplicationTick;
		Category m_Category = Category::EventCategoryApplication;
	};
}

