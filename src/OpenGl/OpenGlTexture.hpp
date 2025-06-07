#pragma once
#include "EngineApi.hpp"
#include"Core/Logger.hpp"

#include "Graphics/Texture.hpp"
class KNIGHT_ENGINE_API OpenGlTexture : public Texture
{
public:
	OpenGlTexture(const char* path);
	virtual ~OpenGlTexture();
	virtual void Bind(unsigned int slot = 0) const override;
	virtual void Unbind() const override;
	virtual unsigned int GetWidth() const override;
	virtual unsigned int GetHeight() const override;
	virtual unsigned int GetID() const override;

	
};

