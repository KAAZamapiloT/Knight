#pragma once
#include "EngineApi.hpp"
#include"Graphics/Texture.hpp"
class KNIGHT_ENGINE_API Material
{
public:
	virtual void bind() const=0;
private:
	Texture* m_DiffuseTexture;
	Texture* m_SpecularTexture;
	int m_Shininess;
	int m_Opacity;
	int m_Emissive;
	int m_Reflective;
	int m_RefractionIndex;
	int m_metallic;
};

