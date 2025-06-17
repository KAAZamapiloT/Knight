#pragma once
#include"EngineApi.hpp"
#include "Event/Event.hpp"
#include"Core/Logger.hpp"
/**
 * @class ApplicationEvents
 * @brief Contains all application-level events.
 *
 * This class serves as a namespace for application-specific events,
 * allowing for better organization and management of event types.
 */
class KNIGHT_ENGINE_API ApplicationEvents :public Event
{
public:
	ApplicationEvents(std::string Name):m_Name(Name){
		SetName(Name);
		KE_TAG_LOG_INFO("ApplicationEvents", "Event created:",Name);
	}
	void Handle() override {
		KE_TAG_LOG_INFO("ApplicationEvents", "Handling event:", GetName());
	}
	std::string GetName() override {
		return m_Name;
	}
	void SetName(const std::string& name) override {
		m_Name = name;
		KE_TAG_LOG_INFO("ApplicationEvents", "Event name set to:", m_Name);
	}
	void SetDimensions(uint32_t width, uint32_t height);
private:
	std::string m_Name; ///< Name of the event, useful for debugging/logging.
	
	uint32_t m_Width, m_Height; ///< Dimensions of the application window.
	uint32_t m_FPS; ///< Frames per second for the application.
};

