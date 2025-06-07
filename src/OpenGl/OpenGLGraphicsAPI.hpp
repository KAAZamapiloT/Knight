#pragma once
#include "EngineApi.hpp"
#include "Graphics/GraphicsApi.hpp"
class KNIGHT_ENGINE_API OpenGLGraphicsAPI : public Knight::GraphicsAPI
{
public:
	OpenGLGraphicsAPI() = default;
	~OpenGLGraphicsAPI() = default;
	void Init() override;
		// Initialize OpenGL context and settings
	
	void Clear(float r, float g, float b, float a) override; 
		// Clear the screen with the specified color
	void SetViewport(int x, int y, int width, int height) override;

	// Set the viewport dimensions and position
	void Draw() ;
		
	void DrawIndexed(unsigned int indexCount) override;
		
		
	
	void Present();
	// Swap buffers to present the rendered frame
private:
	unsigned int m_VWidth = 800;
	unsigned int m_VHeight = 600;
	
};

