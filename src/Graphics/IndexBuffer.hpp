#pragma once
#include "EngineApi.hpp"
#include <memory>
class KNIGHT_ENGINE_API IndexBuffer {
public:
	virtual ~IndexBuffer() = default;
	virtual void Bind()const  = 0;
	virtual void Unbind()const = 0;
	static IndexBuffer* Create(uint32_t* indices, uint32_t count);

};