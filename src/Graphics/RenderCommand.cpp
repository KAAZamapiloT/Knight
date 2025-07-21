#include "RenderCommand.hpp"
#include"Renderer.hpp"
namespace Knight {
	std::unique_ptr<GraphicsAPI> RenderCommand::s_RendererAPI = CreateGraphicsAPI();

}