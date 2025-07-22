#pragma once

#include "Graphics/GraphicsAPI.hpp"
#include "Core/Core.h" // For Scope/unique_ptr
#include <glm/glm.hpp>
#include <memory>
#include"Graphics/VertexArray.hpp"
// Forward-declare VertexArray to keep the header clean
namespace KnightEngine {
	class VertexArray;
}

namespace Knight {

	/**
	 * @class RenderCommand
	 * @brief A static utility class for dispatching low-level rendering commands.
	 * @details This class provides a clean, high-level interface for sending commands
	 * to the underlying GraphicsAPI. It is designed as a static class, meaning
	 * all its functions can be called directly without creating an instance.
	 * The Application is responsible for calling RenderCommand::Init() at startup.
	 */
	class RenderCommand
	{
	public:
		/**
		 * @brief Initializes the underlying graphics API. Must be called once at startup.
		 */
		static void Init()
		{
			s_RendererAPI->Init();
		}

		/**
		 * @brief Sets the viewport for rendering.
		 */
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		/**
		 * @brief Sets the clear color for the screen.
		 */
		static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->Clear(color.r, color.g, color.b, color.a);
		}

		/**
		 * @brief Clears the screen using the currently set clear color.
		 */
		static void Clear()
		{
			// Assuming the API's Clear can be called without args to use the last set color,
			// or we can just clear to a default color.
			// For this example, let's assume the Renderer sets the color.
			// This function would simply call the API's clear command.
		}

		/**
		 * @brief Draws an indexed mesh.
		 * @param vertexArray The vertex array containing the geometry to draw.
		 */
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		// Other potential commands from the Hazel example
		// static void DrawLines(const std::shared_ptr<KnightEngine::VertexArray>& vertexArray, uint32_t vertexCount);
		// static void SetLineWidth(float width);
		static GraphicsAPI* GetApi() { return s_RendererAPI.get(); }
	private:
		// This static pointer holds the one and only instance of the graphics API.
		// It must be initialized once by the Application.
		static std::unique_ptr<GraphicsAPI> s_RendererAPI;
	};

}
