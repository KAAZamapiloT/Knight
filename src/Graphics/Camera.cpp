#include "Camera.hpp"
#include <algorithm>

namespace Knight {

    // Perspective constructor
    Camera::Camera(float fov, float aspect, float nearPlane, float farPlane)
        : m_Type(ECameraType::Perspective)
        , m_FOV(fov)
        , m_AspectRatio(aspect)
        , m_NearPlane(nearPlane)
        , m_FarPlane(farPlane)
    {
        SetFOV(fov); // clamping it in case it went wrong 

        UpdateMatrices();
    }

    // Orthographic constructor
    Camera::Camera(float left, float right, float bottom, float top, float nearPlane, float farPlane)
        : m_Type(ECameraType::Orthographic)
        , m_OrthoLeft(left)
        , m_OrthoRight(right)
        , m_OrthoBottom(bottom)
        , m_OrthoTop(top)
        , m_NearPlane(nearPlane)
        , m_FarPlane(farPlane)
    {
        UpdateMatrices();
    }

    void Camera::SetPosition(const vec3& position) {
        m_Position = position;
        m_ViewDirty = true;
    }

    void Camera::SetRotation(const Quat& rotation) {
        m_Rotation = glm::normalize(rotation);
        m_ViewDirty = true;
    }

    void Camera::SetTarget(const vec3& target) {
        m_Target = target;
    }

    void Camera::LookAt(const vec3& target, const vec3& up) {
        m_Target = target;
        vec3 forward = glm::normalize(target - m_Position);
        vec3 right = glm::normalize(glm::cross(forward, up));
        vec3 newUp = glm::cross(right, forward);

        // Create rotation matrix and convert to quaternion
        MAT4x4 rotMatrix = MAT4x4(1.0f);
        rotMatrix[0] = vec4(right, 0);
        rotMatrix[1] = vec4(newUp, 0);
        rotMatrix[2] = vec4(-forward, 0); // Negative because we're looking down -Z

        m_Rotation = glm::quat_cast(rotMatrix);
        m_ViewDirty = true;
    }

    void Camera::SetFOV(float fov) {
        m_FOV = glm::clamp(fov, 1.0f, 179.0f);
        m_ProjectionDirty = true;
    }

    void Camera::SetAspectRatio(float aspect) {
        m_AspectRatio = aspect;
        m_ProjectionDirty = true;
    }

    void Camera::SetNearFar(float nearPlane, float farPlane) {
        m_NearPlane = nearPlane;
        m_FarPlane = farPlane;
        m_ProjectionDirty = true;
    }

    void Camera::SetOrthoBounds(float left, float right, float bottom, float top) {
        m_OrthoLeft = left;
        m_OrthoRight = right;
        m_OrthoBottom = bottom;
        m_OrthoTop = top;
        m_ProjectionDirty = true;
    }

    void Camera::SetType(ECameraType type) {
        m_Type = type;
        m_ProjectionDirty = true;
    }

    void Camera::MoveForward(float distance) {
        m_Position += GetForwardVector() * distance;
        m_ViewDirty = true;
    }

    void Camera::MoveRight(float distance) {
        m_Position += GetRightVector() * distance;
        m_ViewDirty = true;
    }

    void Camera::MoveUp(float distance) {
        m_Position += GetUpVector() * distance;
        m_ViewDirty = true;
    }

    void Camera::RotateYaw(float angle) {
        m_Yaw += angle;
        Quat yawRotation = glm::angleAxis(angle, vec3(0, 1, 0));
        m_Rotation = yawRotation * m_Rotation;
        m_ViewDirty = true;
    }

    void Camera::RotatePitch(float angle) {
        m_Pitch += angle;
        ClampPitch();

        vec3 right = GetRightVector();
        Quat pitchRotation = glm::angleAxis(angle, right);
        m_Rotation = pitchRotation * m_Rotation;
        m_ViewDirty = true;
    }

    void Camera::RotateRoll(float angle) {
        m_Roll += angle;
        vec3 forward = GetForwardVector();
        Quat rollRotation = glm::angleAxis(angle, forward);
        m_Rotation = rollRotation * m_Rotation;
        m_ViewDirty = true;
    }

    void Camera::RotateFirstPerson(float deltaYaw, float deltaPitch) {
        m_Yaw += deltaYaw;
        m_Pitch += deltaPitch;
        ClampPitch();

        // Build rotation from scratch to avoid accumulating errors
        Quat yawRotation = glm::angleAxis(m_Yaw, vec3(0, 1, 0));
        Quat pitchRotation = glm::angleAxis(m_Pitch, vec3(1, 0, 0));
        Quat rollRotation = glm::angleAxis(m_Roll, vec3(0, 0, 1));

        m_Rotation = yawRotation * pitchRotation * rollRotation;
        m_ViewDirty = true;
    }

    void Camera::RotateAroundTarget(float deltaYaw, float deltaPitch) {
        vec3 direction = m_Position - m_Target;
        float distance = glm::length(direction);

        if (distance < 0.001f) return; // Avoid division by zero

        // Convert to spherical coordinates
        float phi = atan2(direction.z, direction.x) + deltaYaw;
        float theta = acos(direction.y / distance) + deltaPitch;

        // Clamp theta to avoid flipping
        theta = glm::clamp(theta, 0.01f, 3.14159f - 0.01f);

        // Convert back to Cartesian
        vec3 newDirection = vec3(
            sin(theta) * cos(phi),
            cos(theta),
            sin(theta) * sin(phi)
        ) * distance;

        m_Position = m_Target + newDirection;
        LookAt(m_Target);
    }

 

    void Camera::UpdateMatrices() {
        if (m_ViewDirty) {
            UpdateViewMatrix();
            m_ViewDirty = false;
        }

        if (m_ProjectionDirty) {
            UpdateProjectionMatrix();
            m_ProjectionDirty = false;
        }
    }

    void Camera::UpdateViewMatrix() {
        MAT4x4 rotationMatrix = glm::mat4_cast(glm::conjugate(m_Rotation));
        MAT4x4 translationMatrix = glm::translate(MAT4x4(1.0f), -m_Position);
        m_ViewMatrix = rotationMatrix * translationMatrix;
    }

    void Camera::UpdateProjectionMatrix() {
        if (m_Type == ECameraType::Perspective) {
            m_ProjectionMatrix = glm::perspective(
                glm::radians(m_FOV),
                m_AspectRatio,
                m_NearPlane,
                m_FarPlane
            );
        }
        else {
            m_ProjectionMatrix = glm::ortho(
                m_OrthoLeft, m_OrthoRight,
                m_OrthoBottom, m_OrthoTop,
                m_NearPlane, m_FarPlane
            );
        }
    }

    void Camera::ClampPitch() {
        const float maxPitch = 89.0f * 3.14159f / 180.0f; // 89 degrees in radians
        m_Pitch = glm::clamp(m_Pitch, -maxPitch, maxPitch);
        
    }
    
}