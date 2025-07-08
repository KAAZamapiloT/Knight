#include "Camera.hpp"



void Knight::Camera::SetPosition(const vec3 position)
{
	m_Position = position;
	UpdateView();
}

void Knight::Camera::SetUpVector(const vec3 vektor)
{
	m_UpVector = vektor;
	UpdateView();
}

void Knight::Camera::SetForwardVector(const vec3 vektor)
{
	m_ForwardVector = vektor;
	UpdateView();
}

void Knight::Camera::SetType(ECameraType Type)
{
	m_Type = Type;
	UpdateProjection();
}

void Knight::Camera::SetScale(float scale)
{
	OrthoScale = scale;
	UpdateProjection();
}

void Knight::Camera::resize(float aspect)
{
	Aspect = aspect;
	UpdateProjection();
}

void Knight::Camera::UpdateView()
{
	ViewMatrix = glm::lookAt(m_Position, m_ForwardVector, m_UpVector);
}
void Knight::Camera::UpdateProjection()
{
	if (m_Type == ECameraType::Orthographic) {
		float halfHeight = OrthoScale / 2.0f;
		float halfWidth = halfHeight * Aspect;
		ProjectionMatrix = glm::ortho(
			-halfWidth, halfWidth,
			-halfHeight, halfHeight,
			NearView, FarView);
	}
	else {
		ProjectionMatrix = glm::perspective(
			glm::radians(FOV),
			Aspect,
			NearView, FarView);
	}
}


