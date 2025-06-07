#include "OpenGLGraphicsAPI.h"
#include"glad/glad.h"
#include"SDL3/SDL.h"
#include "Core/Logger.hpp"
void OpenGLGraphicsAPI::Init()
{
	if (!gladLoadGL()){
		KE_TAG_LOG_CRITICAL("OpenGLGraphicsAPI", "Failed to initialize GLAD");
		return;
	}
	KE_TAG_LOG_DEBUG("OpenGLGraphicsAPI", "OpenGL initialized successfully");
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, m_VWidth, m_VHeight);
}

void OpenGLGraphicsAPI::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);

	// 2. Clear the framebuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLGraphicsAPI::Draw()
{

}

void OpenGLGraphicsAPI::Present()
{
}
