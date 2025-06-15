#pragma once
#include"EngineApi.hpp"
#include "Event/Event.hpp"
#include  "Event/EventQueue.hpp"
namespace KnightEngine{
class KNIGHT_ENGINE_API EventBus
{
public:
	EventQueue GetQueue() { return Buffer; }
private:
	std::unordered_map<std::string, std::function<void(Event&)>> m_EventCallbacks; 
	EventQueue Buffer;
};
}

