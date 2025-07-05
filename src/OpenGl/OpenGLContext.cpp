#include "OpenGLContext.hpp"

void KnightEngine::OpenGLContext::Init()
{
	m_GLContext = SDL_GL_CreateContext(m_Window);
	SDL_GL_MakeCurrent(m_Window, m_GLContext);
	int status = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
	if (!status) {
		KE_TAG_LOG_CRITICAL("OpenGLContext", "Failed to initialize GLAD");
		return;
	}
	else {
		KE_TAG_LOG_INFO("OpenGLContext", "OpenGL context initialized successfully for window: {}", SDL_GetWindowTitle(m_Window));
	}

}

void KnightEngine::OpenGLContext::SwapBuffers()
{
	SwapBuffers();
}
