#pragma once
class OpenGLGraphicsAPI
{
public:
	OpenGLGraphicsAPI() = default;
	~OpenGLGraphicsAPI() = default;
	void Init() {
		// Initialize OpenGL context and settings
	}
	void Clear(float r, float g, float b, float a) {
		// Clear the screen with the specified color
	}
	void Draw() {
		// Draw the scene
	}
	void Present() {
		// Swap buffers to present the rendered frame
	}
};

