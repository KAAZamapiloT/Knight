#pragma once
#include"EngineApi.hpp"
#include "Engine.hpp"
#include "Event/Event.hpp"
namespace KnightEngine {
	class KNIGHT_ENGINE_API EventHandler
	{
	public:
		
	private:
		std::unordered_map<std::string,void(Event&)> m_EventCallbacks;
	};
}


// ROLE OF EVENT HANDLER IS TO PROCESS MESAGES LISTENED BY EVENT DISPACTCHER
