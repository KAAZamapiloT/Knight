#pragma once
class ForwardRenderer
{

public:
	void init();
	void SubmitCommandBuffer();
	void beginFrame();
	void render();
	void endFrame();
	
};

