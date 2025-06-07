#pragma once
#include "EngineApi.hpp"
#include "Graphics/Material.hpp"
#include"utils/Math.hpp"
class KNIGHT_ENGINE_API Mesh
{
private:
	Material* m_Material;
	glm::mat4 m_Transform;
	glm::vec3 m_Position;
};

