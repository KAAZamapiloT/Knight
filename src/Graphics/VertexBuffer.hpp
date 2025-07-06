#pragma once
#include "EngineApi.hpp"

#include<memory>
class KNIGHT_ENGINE_API VertexBuffer {
public:
	
virtual	void Bind()const =0;
virtual	void Unbind()const =0;
virtual ~VertexBuffer() {}
static VertexBuffer* Create(float* data, uint32_t size);

};