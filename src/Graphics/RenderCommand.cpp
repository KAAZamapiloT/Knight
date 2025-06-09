#include "RenderCommand.hpp"

namespace Knight {
	std::unique_ptr<GraphicsAPI> RenderCommand::s_API = nullptr;
	
	RenderCommand::RenderCommand()
	{
		s_API = CreateGraphicsAPI();
	}

}