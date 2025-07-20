#include "Camera.hpp"
#include "KnightEnginepch.h"
#include "input/InputManager.h"
#include "KeyCodes.h"
#include <algorithm>


using namespace glm;

namespace Knight {

    // --- Constructors ---

    // Perspective constructor
    Camera::Camera(float fov, float aspect, float nearPlane, float farPlane)
        : m_Type(ECameraType::Perspective)
        , m_FOV(glm::clamp(fov, 1.0f, 179.0f))
        , m_AspectRatio(aspect)
        , m_NearPlane(nearPlane)
        , m_FarPlane(farPlane)
    {
        // Initial matrices are calculated upon construction.
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
        // Initial matrices are calculated upon construction.
        UpdateMatrices();
    }

    // --- Setters and Modifiers ---

    void Camera::SetPosition(const vec3& position) {
        if (m_Position != position) {
            m_Position = position;
            m_ViewDirty = true;
        }
    }

    void Camera::SetRotation(const Quat& rotation) {
        Quat normalizedRotation = glm::normalize(rotation);
        if (m_Rotation != normalizedRotation) {
            m_Rotation = normalizedRotation;
            // TODO: Decompose quaternion to update m_Yaw, m_Pitch, m_Roll for consistency
            m_ViewDirty = true;
        }
    }

    void Camera::SetTarget(const vec3& target) {
        if (m_Target != target) {
            m_Target = target;
        }
    }

    void Camera::LookAt(const vec3& target, const vec3& up) {
        m_Target = target;
        m_Rotation = glm::quatLookAt(glm::normalize(target - m_Position), up);
        // TODO: Decompose quaternion to update m_Yaw, m_Pitch, m_Roll for consistency
        m_ViewDirty = true;
    }

    void Camera::SetPerspective(float fov, float aspect, float nearPlane, float farPlane)
    {
        bool changed = false;
        float clampedFov = glm::clamp(fov, 1.0f, 179.0f);

        if (m_Type != ECameraType::Perspective) { m_Type = ECameraType::Perspective; changed = true; }
        if (m_FOV != clampedFov) { m_FOV = clampedFov; changed = true; }
        if (m_AspectRatio != aspect) { m_AspectRatio = aspect; changed = true; }
        if (m_NearPlane != nearPlane) { m_NearPlane = nearPlane; changed = true; }
        if (m_FarPlane != farPlane) { m_FarPlane = farPlane; changed = true; }

        if (changed) {
            m_ProjectionDirty = true;
        }
        UpdateMatrices();
    }

    void Camera::SetOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
    {
        bool changed = false;

        if (m_Type != ECameraType::Orthographic) { m_Type = ECameraType::Orthographic; changed = true; }
        if (m_OrthoLeft != left) { m_OrthoLeft = left; changed = true; }
        if (m_OrthoRight != right) { m_OrthoRight = right; changed = true; }
        if (m_OrthoBottom != bottom) { m_OrthoBottom = bottom; changed = true; }
        if (m_OrthoTop != top) { m_OrthoTop = top; changed = true; }
        if (m_NearPlane != nearPlane) { m_NearPlane = nearPlane; changed = true; }
        if (m_FarPlane != farPlane) { m_FarPlane = farPlane; changed = true; }

        if (changed) {
            m_ProjectionDirty = true;
        }
        UpdateMatrices();
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

    // --- Movement & Rotation (Revised Logic) ---

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
            UpdateRotationFromEuler();
        }
    }

    void Camera::RotatePitch(float angle) {
        if (angle != 0.0f) {
            m_Pitch += angle;
            ClampPitch();
            UpdateRotationFromEuler();
        }
    }

    void Camera::RotateRoll(float angle) {
        if (angle != 0.0f) {
            m_Roll += angle;
            UpdateRotationFromEuler();
        }
    }

    void Camera::RotateFirstPerson(float deltaYaw, float deltaPitch) {
        if (deltaYaw == 0.0f && deltaPitch == 0.0f) return;

        m_Yaw += deltaYaw;
        m_Pitch += deltaPitch;

        ClampPitch();
        UpdateRotationFromEuler();
    }

    void Camera::RotateAroundTarget(float deltaYaw, float deltaPitch) {
        if (deltaYaw == 0.0f && deltaPitch == 0.0f) return;

        vec3 offset = m_Position - m_Target;

        Quat yawRotation = glm::angleAxis(deltaYaw, vec3(0.0f, 1.0f, 0.0f));
        offset = yawRotation * offset;

        vec3 right = glm::normalize(glm::cross(offset, vec3(0.0f, 1.0f, 0.0f)));
        Quat pitchRotation = glm::angleAxis(deltaPitch, right);
        offset = pitchRotation * offset;

        m_Position = m_Target + offset;
        LookAt(m_Target);
    }


    // --- Matrix Updates ---

    void Camera::UpdateMatrices() {
        if (m_ViewDirty) {
            UpdateViewMatrix();
        }
        if (m_ProjectionDirty) {
            UpdateProjectionMatrix();
        }
        if (m_ViewDirty || m_ProjectionDirty) {
            ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
            m_ViewDirty = false;
            m_ProjectionDirty = false;
        }
    }

    // --- Private Helper Functions ---

    void Camera::UpdateViewMatrix() {
        mat4 translationMatrix = glm::translate(mat4(1.0f), -m_Position);
        mat4 rotationMatrix = glm::mat4_cast(glm::conjugate(m_Rotation));
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
        else { // Orthographic
            m_ProjectionMatrix = glm::ortho(
                m_OrthoLeft, m_OrthoRight,
                m_OrthoBottom, m_OrthoTop,
                m_NearPlane, m_FarPlane
            );
        }
    }

    void Camera::UpdateRotationFromEuler() {
        Quat yawRotation = glm::angleAxis(m_Yaw, vec3(0, 1, 0));
        Quat pitchRotation = glm::angleAxis(m_Pitch, vec3(1, 0, 0));
        Quat rollRotation = glm::angleAxis(m_Roll, vec3(0, 0, 1));

        m_Rotation = yawRotation * pitchRotation * rollRotation;
        m_ViewDirty = true;
    }

    void Camera::ClampPitch() {
        constexpr float maxPitch = glm::radians(89.0f);
        m_Pitch = glm::clamp(m_Pitch, -maxPitch, maxPitch);
    }

} // namespace Knight
