#pragma once

#include "EngineApi.hpp"
#include "utils/Math.hpp"
#include "Event/Event.hpp"
#include "Event/EventDispatcher.hpp"
#include "Event/WindowEvent.hpp"
#include "Event/KeyEvent.hpp"
#include "Event/MouseEvent.hpp"

namespace Knight {

    /**
     * @enum ECameraType
     * @brief Defines the projection type of the camera.
     */
    enum class ECameraType {
        Orthographic, ///< Renders the scene without perspective, useful for 2D or isometric views.
        Perspective   ///< Renders the scene with perspective, creating a sense of depth.
    };

    /**
     * @class Camera
     * @brief Represents a camera in a 3D or 2D scene, handling view and projection transformations.
     *
     * This class can function as either a perspective or orthographic camera. It manages
     * its position, rotation, and projection parameters to generate the necessary matrices
     * for rendering. It uses a dirty-flag system to avoid unnecessary matrix recalculations.
     */
    class KNIGHT_ENGINE_API Camera {
    public:
        using MAT4x4 = glm::mat4x4;
        using Quat = glm::quat;
        using vec3 = glm::vec3;
        using vec4 = glm::vec4;

        // --- Constructors ---

        /**
         * @brief Constructs a perspective camera.
         * @param fov Vertical field of view in degrees.
         * @param aspect Aspect ratio (width / height).
         * @param nearPlane The near clipping plane distance.
         * @param farPlane The far clipping plane distance.
         */
        Camera(float fov = 45.0f, float aspect = 16.0f / 9.0f, float nearPlane = 0.1f, float farPlane = 100.0f);

        /**
         * @brief Constructs an orthographic camera.
         * @param left The left boundary of the view frustum.
         * @param right The right boundary of the view frustum.
         * @param bottom The bottom boundary of the view frustum.
         * @param top The top boundary of the view frustum.
         * @param nearPlane The near clipping plane distance.
         * @param farPlane The far clipping plane distance.
         */
        Camera(float left, float right, float bottom, float top, float nearPlane, float farPlane);

        // --- Position and Orientation ---

        /**
         * @brief Sets the absolute world-space position of the camera.
         * @param position The new position.
         * @note Marks the view matrix as dirty.
         */
        void SetPosition(const vec3& position);

        /**
         * @brief Sets the absolute rotation of the camera using a quaternion.
         * @param rotation The new rotation.
         * @note Marks the view matrix as dirty.
         */
        void SetRotation(const Quat& rotation);

        /**
         * @brief Sets the target point for orbit-style cameras.
         * @param target The world-space point to orbit around.
         */
        void SetTarget(const vec3& target);

        /**
         * @brief Rotates the camera to face a specific target point.
         * @param target The world-space point to look at.
         * @param up The world's up direction, used to orient the camera.
         * @note Marks the view matrix as dirty.
         */
        void LookAt(const vec3& target, const vec3& up = vec3(0, 1, 0));

        // --- Projection Configuration ---

        /**
         * @brief Configures the camera for perspective projection.
         * @param fov Vertical field of view in degrees.
         * @param aspect Aspect ratio (width / height).
         * @param nearPlane The near clipping plane distance.
         * @param farPlane The far clipping plane distance.
         * @note Marks the projection matrix as dirty.
         */
        void SetPerspective(float fov = 45.0f, float aspect = 16.0f / 9.0f, float nearPlane = 0.1f, float farPlane = 100.0f);

        /**
         * @brief Configures the camera for orthographic projection.
         * @param left The left boundary of the view frustum.
         * @param right The right boundary of the view frustum.
         * @param bottom The bottom boundary of the view frustum.
         * @param top The top boundary of the view frustum.
         * @param nearPlane The near clipping plane distance.
         * @param farPlane The far clipping plane distance.
         * @note Marks the projection matrix as dirty.
         */
        void SetOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);

        /**
         * @brief Sets the vertical field of view (for perspective cameras).
         * @param fov The new FOV in degrees.
         * @note Marks the projection matrix as dirty.
         */
        void SetFOV(float fov);

        /**
         * @brief Sets the aspect ratio.
         * @param aspect The new aspect ratio (width / height).
         * @note Marks the projection matrix as dirty.
         */
        void SetAspectRatio(float aspect);

        /**
         * @brief Sets the near and far clipping planes.
         * @param nearPlane The new near plane distance.
         * @param farPlane The new far plane distance.
         * @note Marks the projection matrix as dirty.
         */
        void SetNearFar(float nearPlane, float farPlane);

        /**
         * @brief Sets the boundaries for an orthographic camera.
         * @param left The new left boundary.
         * @param right The new right boundary.
         * @param bottom The new bottom boundary.
         * @param top The new top boundary.
         * @note Marks the projection matrix as dirty.
         */
        void SetOrthoBounds(float left, float right, float bottom, float top);

        /**
         * @brief Sets the camera's projection type.
         * @param type The new camera type (Perspective or Orthographic).
         * @note Marks the projection matrix as dirty.
         */
        void SetType(ECameraType type);

        // --- Movement & Rotation ---

        /** @brief Moves the camera along its forward vector. */
        void MoveForward(float distance);
        /** @brief Moves the camera along its right vector. */
        void MoveRight(float distance);
        /** @brief Moves the camera along its up vector. */
        void MoveUp(float distance);

        /** @brief Rotates the camera around its vertical (Y) axis. */
        void RotateYaw(float angle);
        /** @brief Rotates the camera around its horizontal (X) axis. */
        void RotatePitch(float angle);
        /** @brief Rotates the camera around its depth (Z) axis. */
        void RotateRoll(float angle);

        /**
         * @brief Applies yaw and pitch rotations, suitable for first-person controls.
         * @param deltaYaw Change in yaw.
         * @param deltaPitch Change in pitch.
         */
        void RotateFirstPerson(float deltaYaw, float deltaPitch);

        /**
         * @brief Rotates the camera around a target point, suitable for orbit controls.
         * @param deltaYaw Change in yaw around the target.
         * @param deltaPitch Change in pitch around the target.
         */
        void RotateAroundTarget(float deltaYaw, float deltaPitch);

        // --- Getters ---

        /** @return The current projection type of the camera. */
        ECameraType GetType() const { return m_Type; }
        /** @return The current position of the camera. */
        const vec3& GetPosition() const { return m_Position; }
        /** @return The current rotation of the camera as a quaternion. */
        const Quat& GetRotation() const { return m_Rotation; }

        /** @return The camera's forward vector in world space. */
        vec3 GetForwardVector() const { return glm::normalize(m_Rotation * vec3(0, 0, -1)); }
        /** @return The camera's right vector in world space. */
        vec3 GetRightVector() const { return glm::normalize(m_Rotation * vec3(1, 0, 0)); }
        /** @return The camera's up vector in world space. */
        vec3 GetUpVector() const { return glm::normalize(m_Rotation * vec3(0, 1, 0)); }

        /** @return The cached projection matrix. */
        const MAT4x4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        /** @return The cached view matrix. */
        const MAT4x4& GetViewMatrix() const { return m_ViewMatrix; }
        /** @return The cached combined view-projection matrix. */
        const MAT4x4& GetViewProjectionMatrix() const { return ViewProjectionMatrix; }

        /** @return The current vertical field of view (in degrees). */
        float GetFOV() const { return m_FOV; }
        /** @return The current aspect ratio. */
        float GetAspectRatio() const { return m_AspectRatio; }
        /** @return The current near clipping plane distance. */
        float GetNearPlane() const { return m_NearPlane; }
        /** @return The current far clipping plane distance. */
        float GetFarPlane() const { return m_FarPlane; }

        // --- Utility ---

        /**
         * @brief Recalculates view and/or projection matrices if they are dirty.
         * This should be called once per frame before rendering.
         */
        void UpdateMatrices();

    private:
        /// @brief Recalculates the view matrix based on position and rotation.
        void UpdateViewMatrix();
        /// @brief Recalculates the projection matrix based on camera type and its parameters.
        void UpdateProjectionMatrix();
        /// @brief Clamps the pitch angle to prevent the camera from flipping over.
        void ClampPitch();
        /// @brief Updates the main m_Rotation quaternion from the Euler angles (m_Yaw, m_Pitch, m_Roll).
        void UpdateRotationFromEuler();

        // --- Transform Data ---
        vec3 m_Position = vec3(0, 0, 0);   ///< Camera position in world space.
        Quat m_Rotation = Quat(1, 0, 0, 0); ///< Camera orientation in world space.
        vec3 m_Target = vec3(0, 0, -1);    ///< Target point for orbit camera controls.

        // --- Projection Parameters ---
        ECameraType m_Type = ECameraType::Perspective; ///< Current projection type.
        float m_FOV = 45.0f;                           ///< Vertical field of view (degrees).
        float m_AspectRatio = 16.0f / 9.0f;            ///< Viewport aspect ratio.
        float m_NearPlane = 0.1f;                      ///< Near clipping plane.
        float m_FarPlane = 100.0f;                     ///< Far clipping plane.

        // --- Orthographic Bounds ---
        float m_OrthoLeft = -1.0f;
        float m_OrthoRight = 1.0f;
        float m_OrthoBottom = -1.0f;
        float m_OrthoTop = 1.0f;

        // --- Matrices & State ---
        mutable MAT4x4 m_ViewMatrix = MAT4x4(1.0f);         ///< Cached view matrix.
        mutable MAT4x4 m_ProjectionMatrix = MAT4x4(1.0f);   ///< Cached projection matrix.
        mutable MAT4x4 ViewProjectionMatrix = MAT4x4(1.0f); ///< Cached view-projection matrix.
        mutable bool m_ViewDirty = true;                    ///< Flag to rebuild the view matrix.
        mutable bool m_ProjectionDirty = true;              ///< Flag to rebuild the projection matrix.

        // --- Euler Angles for Rotation Control ---
        float m_Yaw = 0.0f;   ///< Rotation around the Y axis.
        float m_Pitch = 0.0f; ///< Rotation around the X axis.
        float m_Roll = 0.0f;  ///< Rotation around the Z axis.
    };
}



//THIS CAMERA IS FOR 3D BUT MAY WORK FOR 2D ALSP