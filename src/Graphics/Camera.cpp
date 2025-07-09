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

void Knight::Camera::RotateFirstPerson(float DeltaYaw, float DeltaPitch)
{
	// Create quaternions for yaw (around Y) and pitch (around X)
	glm::quat yawQuat = glm::angleAxis(glm::radians(DeltaYaw), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat pitchQuat = glm::angleAxis(glm::radians(DeltaPitch), glm::vec3(1.0f, 0.0f, 0.0f));

	// Combine rotations (order matters: yaw then pitch)
	Rotation = glm::normalize(yawQuat * Rotation * pitchQuat);

	// Update target based on forward direction
	glm::vec3 forward =Rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	m_ForwardVector= m_Position+ glm::normalize(forward);

	UpdateView();
}

void Knight::Camera::RotateAroundTarget(float DeltaYaw, float DeltaPitch)
{
	// Create quaternions for yaw (around Y) and pitch (around X)
	glm::quat yawQuat = glm::angleAxis(glm::radians(DeltaYaw), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat pitchQuat = glm::angleAxis(glm::radians(DeltaPitch), glm::vec3(1.0f, 0.0f, 0.0f));

	// Combine rotations (order matters: yaw then pitch)
	Rotation = glm::normalize(yawQuat * Rotation * pitchQuat);

	// Calculate new position by rotating the vector from target to position
	glm::vec3 offset = m_Position - m_ForwardVector;
	offset = Rotation* offset;
	m_Position = m_ForwardVector + offset;

	UpdateView();
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


