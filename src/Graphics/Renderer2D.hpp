#pragma once
#include "EngineApi.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Texture.hpp"
#include <glm/glm.hpp>

namespace Knight {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginFrame(const Camera& camera);
		static void EndFrame();

		// The Flush function is what actually performs the draw call.
		// It's called automatically by EndFrame, but can also be called manually
		// if you need to start a new batch in the middle of a frame (e.g., to change a shader).
		static void Flush();

		// --- Primitives ---

		// Draw a solid-colored quad
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		

		// Draw a solid-colored, rotated quad
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

		

		// Draw a textured, rotated quad
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f));
	};
}
