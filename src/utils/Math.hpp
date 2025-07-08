#pragma once

// Core GLM library: vectors, matrices, basic math
#include <glm/glm.hpp>

// Matrix transformations: translate, rotate, scale, perspective, ortho
#include <glm/gtc/matrix_transform.hpp>

// Pointer access to data (for OpenGL uniform uploads)
#include <glm/gtc/type_ptr.hpp>

// Quaternions for rotations
#include <glm/gtc/quaternion.hpp>

struct Transform {
	glm::vec3 Location;
	glm::vec3 Roataion;
	glm::vec3 Scale;
};

