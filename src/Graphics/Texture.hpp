#pragma once
#include "EngineApi.hpp"
class KNIGHT_ENGINE_API Texture
{
public:
	Texture() = default;
	virtual ~Texture() = default;
	virtual void Bind(unsigned int slot = 0) const = 0;
	virtual void Unbind() const = 0;
	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;
	virtual unsigned int GetID() const = 0;
	static Texture* Create(const char* path);


};

