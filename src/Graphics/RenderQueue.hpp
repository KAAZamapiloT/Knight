#pragma once
#include "EngineApi.hpp"
#include "Graphics/RenderCommand.hpp"
#include<memory>
#include<vector>
namespace Knight
{


	class KNIGHT_ENGINE_API RenderQueue
	{
	public:
		RenderCommand DispatchCommand();
		void AddCommand(const RenderCommand& command);
		void ClearCommands();

	private:
		// A queue to hold render commands
		std::unique_ptr<std::vector<RenderCommand*>> m_RenderCommands;

	};
}

