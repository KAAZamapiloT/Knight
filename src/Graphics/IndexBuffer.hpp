#pragma once
#include "EngineApi.hpp"
#include <memory>
class KNIGHT_ENGINE_API IndexBuffer {
public:
	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	static std::shared_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);

};