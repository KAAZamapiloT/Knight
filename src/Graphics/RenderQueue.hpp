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

		void AddCommand(const RenderCommand& command);
		void ClearCommands();
		std::vector<RenderCommand> GetCommands() { return m_RenderCommands; }
	private:
		// A queue to hold render commands
		std::vector<RenderCommand> m_RenderCommands;

	};
}