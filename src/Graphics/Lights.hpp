#pragma once
#include"EngineApi.hpp"
#include"KnightEnginepch.h"
#include"utils/Math.hpp"
enum class ELightType :UINT8 {
	Spot,
	Directional,
	Rect,
	Point
};

struct KNIGHT_ENGINE_API Light {
    ELightType type;
    glm::vec3 Position;   // Not needed for directional light
    glm::vec3 Direction;  // Needed for directional/spot
    glm::vec3 Color;
    float intensity;

    // Optional: attenuation for point/spot lights
    float constant;
    float linear;
    float quadratic;

    // Optional: spotlight angles
    float innerCutoff;
    float outerCutoff;

};