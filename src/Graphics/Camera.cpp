#include "Camera.hpp"
#include <algorithm>
#include "KnightEnginepch.h"

namespace Knight {

    // Perspective constructor
    Camera::Camera(float fov, float aspect, float nearPlane, float farPlane)
        : m_Type(ECameraType::Perspective)
        , m_FOV(glm::clamp(fov, 1.0f, 179.0f))  // Clamp directly in initializer
        , m_AspectRatio(aspect)
        , m_NearPlane(nearPlane)
        , m_FarPlane(farPlane)
    {
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
        if (m_Position != position) {  // Avoid unnecessary updates
            m_Position = position;
            m_ViewDirty = true;
            UpdateMatrices();
        }
    }

    void Camera::SetRotation(const Quat& rotation) {
        Quat normalizedRotation = glm::normalize(rotation);
        if (m_Rotation != normalizedRotation) {  // Avoid unnecessary updates
            m_Rotation = normalizedRotation;
            m_ViewDirty = true;
            UpdateMatrices();
        }
    }

    void Camera::SetTarget(const vec3& target) {
        if (m_Target != target) {  // Avoid unnecessary updates
            m_Target = target;
            // Note: This doesn't mark view as dirty since target is only used for orbit camera
        }
    }

    void Camera::LookAt(const vec3& target, const vec3& up) {
        m_Target = target;

        vec3 forward = glm::normalize(target - m_Position);

        // Check if forward and up are parallel (avoid singularity)
        if (abs(glm::dot(forward, up)) > 0.999f) {
            // Use a different up vector if they're nearly parallel
            vec3 alternateUp = (abs(up.y) < 0.9f) ? vec3(0, 1, 0) : vec3(1, 0, 0);
            m_Rotation = glm::quatLookAt(forward, alternateUp);
        }
        else {
            m_Rotation = glm::quatLookAt(forward, up);
        }

        m_ViewDirty = true;
    }

    void Camera::SetFOV(float fov) {
        float clampedFov = glm::clamp(fov, 1.0f, 179.0f);
        if (m_FOV != clampedFov) {
            m_FOV = clampedFov;
            m_ProjectionDirty = true;
        }
    }

    void Camera::SetAspectRatio(float aspect) {
        if (m_AspectRatio != aspect) {
            m_AspectRatio = aspect;
            m_ProjectionDirty = true;
        }
    }

    void Camera::SetNearFar(float nearPlane, float farPlane) {
        if (m_NearPlane != nearPlane || m_FarPlane != farPlane) {
            m_NearPlane = nearPlane;
            m_FarPlane = farPlane;
            m_ProjectionDirty = true;
        }
    }

    void Camera::SetOrthoBounds(float left, float right, float bottom, float top) {
        if (m_OrthoLeft != left || m_OrthoRight != right ||
            m_OrthoBottom != bottom || m_OrthoTop != top) {
            m_OrthoLeft = left;
            m_OrthoRight = right;
            m_OrthoBottom = bottom;
            m_OrthoTop = top;
            m_ProjectionDirty = true;
        }
    }

    void Camera::SetType(ECameraType type) {
        if (m_Type != type) {
            m_Type = type;
            m_ProjectionDirty = true;
        }
    }

    void Camera::MoveForward(float distance) {
        if (distance != 0.0f) {
            m_Position += GetForwardVector() * distance;
            m_ViewDirty = true;
        }
    }

    void Camera::MoveRight(float distance) {
        if (distance != 0.0f) {
            m_Position += GetRightVector() * distance;
            m_ViewDirty = true;
        }
    }

    void Camera::MoveUp(float distance) {
        if (distance != 0.0f) {
            m_Position += GetUpVector() * distance;
            m_ViewDirty = true;
        }
    }

    void Camera::RotateYaw(float angle) {
        if (angle != 0.0f) {
            m_Yaw += angle;
            // Apply rotation in world space for yaw
            Quat yawRotation = glm::angleAxis(angle, vec3(0, 1, 0));
            m_Rotation = yawRotation * m_Rotation;
            m_ViewDirty = true;
        }
    }

    void Camera::RotatePitch(float angle) {
        if (angle != 0.0f) {
            float oldPitch = m_Pitch;
            m_Pitch += angle;
            ClampPitch();

            // Only apply rotation if pitch actually changed after clamping
            if (m_Pitch != oldPitch) {
                vec3 right = GetRightVector();
                Quat pitchRotation = glm::angleAxis(m_Pitch - oldPitch, right);
                m_Rotation = pitchRotation * m_Rotation;
                m_ViewDirty = true;
            }
        }
    }

    void Camera::RotateRoll(float angle) {
        if (angle != 0.0f) {
            m_Roll += angle;
            vec3 forward = GetForwardVector();
            Quat rollRotation = glm::angleAxis(angle, forward);
            m_Rotation = rollRotation * m_Rotation;
            m_ViewDirty = true;
        }
    }

    void Camera::RotateFirstPerson(float deltaYaw, float deltaPitch) {
        if (deltaYaw != 0.0f || deltaPitch != 0.0f) {
            m_Yaw += deltaYaw;
            m_Pitch += deltaPitch;
            ClampPitch();

            // Order: Yaw (Y) * Pitch (X) * Roll (Z) - this is the standard order
            Quat yawRotation = glm::angleAxis(m_Yaw, vec3(0, 1, 0));
            Quat pitchRotation = glm::angleAxis(m_Pitch, vec3(1, 0, 0));
            Quat rollRotation = glm::angleAxis(m_Roll, vec3(0, 0, 1));

            m_Rotation = yawRotation * pitchRotation * rollRotation;
            m_ViewDirty = true;
        }
    }

    void Camera::RotateAroundTarget(float deltaYaw, float deltaPitch) {
        if (deltaYaw == 0.0f && deltaPitch == 0.0f) return;

        vec3 direction = m_Position - m_Target;
        float distance = glm::length(direction);

        if (distance < 0.001f) return; // Avoid division by zero

        // Convert to spherical coordinates
        float phi = atan2(direction.z, direction.x) + deltaYaw;
        float theta = acos(glm::clamp(direction.y / distance, -1.0f, 1.0f)) + deltaPitch;

        // Clamp theta to avoid flipping
        constexpr float epsilon = 0.01f;
        constexpr float pi = 3.14159265359f;
        theta = glm::clamp(theta, epsilon, pi - epsilon);

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
        ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera::UpdateViewMatrix() {
        // More efficient view matrix calculation
        MAT4x4 translationMatrix = glm::translate(MAT4x4(1.0f), -m_Position);
        MAT4x4 rotationMatrix = glm::mat4_cast(glm::conjugate(m_Rotation));
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
        constexpr float maxPitch = 89.0f * 3.14159265359f / 180.0f; // Use constexpr for compile-time constant
        m_Pitch = glm::clamp(m_Pitch, -maxPitch, maxPitch);
    }
}