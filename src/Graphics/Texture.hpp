#pragma once
#include "EngineApi.hpp"
class KNIGHT_ENGINE_API Texture
{
public:
	Texture() = default;
	virtual ~Texture() = default;
	virtual void Bind(unsigned int slot = 0) const = 0;
	virtual void Unbind() const = 0;
	virtual unsigned int GetWidth() const { return m_Width; }
	virtual unsigned int GetHeight() const { return m_Height; }
	virtual unsigned int GetID() const { return m_ID; }
	static Texture* Create(const char* path);

private:
	unsigned int m_ID = 0;
	unsigned int m_Width = 0;
	unsigned int m_Height = 0;
	unsigned int m_InternalFormat = 0;
	unsigned int m_DataFormat = 0;
	const char* m_Path = nullptr;
	const char* m_Name = nullptr;
};

