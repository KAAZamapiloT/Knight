#pragma once
#include"EngineApi.hpp"
#include "Engine.hpp"
#include "Event/Event.hpp"
namespace KnightEngine {
	class KNIGHT_ENGINE_API EventHandler
	{
	public:
		EventHandler(const std::string& name)
			: m_Name(name) {
		}
		virtual ~EventHandler() = default;
		virtual void HandleEvent(Event& event) = 0;
	private:
		std::string m_Name;
	};
}


// ROLE OF EVENT HANDLER IS TO PROCESS MESAGES LISTENED BY EVENT DISPACTCHER
