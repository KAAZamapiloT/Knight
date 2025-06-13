#pragma once
#include "EngineApi.hpp"

#include<memory>
class KNIGHT_ENGINE_API VertexBuffer {
public:
	
virtual	void Bind()=0;
virtual	void Unbind()=0;

static std::shared_ptr<VertexBuffer> Create(float* data, uint32_t size);

};