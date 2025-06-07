#pragma once
#include "EngineApi.hpp"
class KNIGHT_ENGINE_API ForwardRenderer
{

public:
	void init();
	void SubmitCommandBuffer();
	void beginFrame();
	void render();
	void endFrame();
	
};

