#pragma once
#include "Graphics/GraphicsAPI.hpp"
#include "OpenGl/OpenGLGraphicsAPI.hpp"
#include <memory>
#include"Core/Logger.hpp"
namespace Knight {
    std::unique_ptr<GraphicsAPI> CreateGraphicsAPI();
}
