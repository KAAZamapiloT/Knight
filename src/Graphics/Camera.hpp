#pragma once
#include "EngineApi.hpp"
#include "utils/Math.hpp"
#include"Event/Event.hpp"
#include"Event/EventDispatcher.hpp"
#include"Event/WindowEvent.hpp"
#include"Event/KeyEvent.hpp"
#include"Event/MouseEvent.hpp"
namespace Knight {
    enum class ECameraType { Orthographic, Perspective };

    class KNIGHT_ENGINE_API Camera {
    public:
        using MAT4x4 = glm::mat4x4;
        using Quat = glm::quat;
        using vec3 = glm::vec3;
        using vec4 = glm::vec4;
        // Perspective camera constructor
        Camera(float fov = 45.0f, float aspect = 16.0f / 9.0f, float nearPlane = 0.1f, float farPlane = 100.0f);

        // Orthographic camera constructor
        Camera(float left, float right, float bottom, float top, float nearPlane, float farPlane);

        // Position and orientation
        void SetPosition(const vec3& position);
        void SetRotation(const Quat& rotation);
        void SetTarget(const vec3& target); // Look at target
        void LookAt(const vec3& target, const vec3& up = vec3(0, 1, 0));

        // Camera parameters
        void SetFOV(float fov); // For perspective
        void SetAspectRatio(float aspect);
        void SetNearFar(float nearPlane, float farPlane);
        void SetOrthoBounds(float left, float right, float bottom, float top); // For orthographic
        void SetType(ECameraType type);

        // Movement (first person style)
        void MoveForward(float distance);
        void MoveRight(float distance);
        void MoveUp(float distance);

        // Rotation
        void RotateYaw(float angle);   // Y-axis rotation
        void RotatePitch(float angle); // X-axis rotation
        void RotateRoll(float angle);  // Z-axis rotation
        void RotateFirstPerson(float deltaYaw, float deltaPitch);
        void RotateAroundTarget(float deltaYaw, float deltaPitch);

        // Getters
        ECameraType GetType() const { return m_Type; }
        const vec3& GetPosition() const { return m_Position; }
        const Quat& GetRotation() const { return m_Rotation; }
        vec3 GetForwardVector() const{ return glm::normalize(m_Rotation * vec3(0, 0, -1));
        }
        vec3 GetRightVector() const{ return glm::normalize(m_Rotation * vec3(1, 0, 0)); }
        vec3 GetUpVector() const{ return glm::normalize(m_Rotation * vec3(0, 1, 0)); }

        const MAT4x4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const MAT4x4& GetViewMatrix() const { return m_ViewMatrix; }
        MAT4x4 GetViewProjectionMatrix() const { return ViewProjectionMatrix; }

        float GetFOV() const { return m_FOV; }
        float GetAspectRatio() const { return m_AspectRatio; }
        float GetNearPlane() const { return m_NearPlane; }
        float GetFarPlane() const { return m_FarPlane; }

        // Utility
        void UpdateMatrices();

        
       

    private:
        void UpdateViewMatrix();
        void UpdateProjectionMatrix();
        void ClampPitch(); // Prevent camera from flipping over

        // Transform
        vec3 m_Position = vec3(0, 0, 0);
        Quat m_Rotation = Quat(1, 0, 0, 0); // Identity quaternion
        vec3 m_Target = vec3(0, 0, -1); // For orbit camera
        
        // Camera parameters
        ECameraType m_Type = ECameraType::Perspective;
        float m_FOV = 45.0f;
        float m_AspectRatio = 16.0f / 9.0f;
        float m_NearPlane = 0.1f;
        float m_FarPlane = 100.0f;

        // Orthographic bounds
        float m_OrthoLeft = -1.0f;
        float m_OrthoRight = 1.0f;
        float m_OrthoBottom = -1.0f;
        float m_OrthoTop = 1.0f;

        // Matrices
        mutable MAT4x4 m_ViewMatrix = MAT4x4(1.0f);
        mutable MAT4x4 m_ProjectionMatrix = MAT4x4(1.0f);
        mutable MAT4x4 ViewProjectionMatrix;
        mutable bool m_ViewDirty = true;
        mutable bool m_ProjectionDirty = true;

        // Euler angles for first person rotation (to avoid gimbal lock issues)
        float m_Yaw = 0.0f;
        float m_Pitch = 0.0f;
        float m_Roll = 0.0f;
    };
}


// THIS CAMERA IS SUPPOSED TO BE A 3D CAMERA MAY WORK FOR 2D ALSO 