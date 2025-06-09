/**
 * @file GraphicsFactory.hpp
 * @brief Declares the graphics API factory function for KnightEngine.
 *
 * This file defines the factory method for creating a graphics backend
 * implementation (currently OpenGL). It provides abstraction so the rest of
 * the engine doesn't depend on a specific graphics API.
 */


#pragma once
#include "Graphics/GraphicsApi.hpp"
#include "OpenGl/OpenGLGraphicsAPI.hpp"
#include <memory>
#include"Core/Logger.hpp"

namespace Knight {
    /**
 * @brief Creates an instance of the active GraphicsAPI implementation.
 *
 * @details This function dynamically selects and returns a `GraphicsAPI`
 * implementation using `std::unique_ptr`. By default, it returns an OpenGL-based
 * implementation (`OpenGLGraphicsAPI`), but can be extended to support Vulkan, DirectX, etc.
 *
 * @return std::unique_ptr<GraphicsAPI> A smart pointer to the initialized graphics API.
 *
 * @note Users of this function should not rely on the specific type returned.
 * Use the base `GraphicsAPI` interface for interaction.
 *
 * @example
 * auto api = Knight::CreateGraphicsAPI();
 * api->Init(); // Generic API usage
 */
    KNIGHT_ENGINE_API std::unique_ptr<GraphicsAPI> CreateGraphicsAPI();
}
