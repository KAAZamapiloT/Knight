#pragma once
#include "EngineApi.hpp"
#include <memory>
#include"Core/Core.h"


class KNIGHT_ENGINE_API IndexBuffer {
public:
	virtual ~IndexBuffer() = default;
	virtual void Bind()const  = 0;
	virtual void Unbind()const = 0;
	static Knight::Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	virtual uint32_t GetSize() const = 0;
	virtual inline uint32_t GetCount() = 0;
};