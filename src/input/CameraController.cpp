// This define is required by the GLM library to use experimental features
// like eulerAngles. It must be defined before any GLM headers are included.
#define GLM_ENABLE_EXPERIMENTAL

#include "CameraController.hpp"
#include "input/InputManager.h"
#include "KeyCodes.h" // Assuming this contains your key code definitions (e.g., KnightK_W)
#include "Event/EventDispatcher.hpp"
#include "Event/MouseEvent.hpp"
#include "Event/WindowEvent.hpp"
#include "Event/KeyEvent.hpp"
#include "Core/Logger.hpp" // For KE_TAG_LOG_DEBUG
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <algorithm> // For std::max

namespace Knight {

    // --- Constructor ---
    CameraController::CameraController(float aspectRatio, ECameraType type)
        : m_AspectRatio(aspectRatio)
    {
        if (type == ECameraType::Perspective) {
            M_Camera = Camera(45.0f, m_AspectRatio, 0.1f, 1000.0f);
            M_Camera.SetPosition({ 0.0f, 0.0f, 5.0f });
        }
        else {
            float left = -m_AspectRatio * m_ZoomLevel;
            float right = m_AspectRatio * m_ZoomLevel;
            float bottom = -m_ZoomLevel;
            float top = m_ZoomLevel;
            M_Camera = Camera(left, right, bottom, top, -1.0f, 1.0f);
        }

        // Initialize with practical speed and sensitivity values.
        M_CameraSpeed = 5.0f;         // Units per second
        M_CameraRotationSpeed = 180.0f; // Degrees per second
        m_MouseSensitivity = 0.2f;      // Increased default sensitivity
    }

    // --- OnUpdate (Handles continuous input polling) ---
    void CameraController::OnUpdate(KnightEngine::TimeStamp ts)
    {
        const float speed = M_CameraSpeed * (float)ts;
        bool moved = false;
        const float rotationSpeed = M_CameraRotationSpeed * (float)ts;
        bool rotated = false;
        if (M_Camera.GetType() == ECameraType::Orthographic) {
            // --- Orthographic Camera Controls (2D Top-Down) ---
            glm::vec3 pos = M_Camera.GetPosition();
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_W, 0)) { pos.y += speed; moved = true; }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_S, 0)) { pos.y -= speed; moved = true; }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_A, 0)) { pos.x -= speed; moved = true; }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_D, 0)) { pos.x += speed; moved = true; }
            if (moved) M_Camera.SetPosition(pos);

            // Rotation with arrow keys
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_LEFT, 0)) { M_Camera.RotateRoll(rotationSpeed); rotated = true; }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_RIGHT, 0)) { M_Camera.RotateRoll(-rotationSpeed); rotated = true; }
        }
        else {
            // --- Keyboard Movement (Direct Polling) ---
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_W, 0)) { M_Camera.MoveForward(speed); moved = true; }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_S, 0)) { M_Camera.MoveForward(-speed); moved = true; }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_A, 0)) { M_Camera.MoveRight(-speed); moved = true; }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_D, 0)) { M_Camera.MoveRight(speed); moved = true; }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_E, 0)) { M_Camera.MoveUp(speed); moved = true; }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_Q, 0)) { M_Camera.MoveUp(-speed); moved = true; }
        }
        

        if (moved) {
            const auto& pos = M_Camera.GetPosition();
            KE_TAG_LOG_DEBUG("CameraController", "Movement detected. New Position: ({:.2f}, {:.2f}, {:.2f})", pos.x, pos.y, pos.z);
        }

        // --- Mouse Rotation ---
        if (m_MouseRotationEnabled) {
            glm::vec2 mousePos = KnightEngine::InputManager::GetMousePositionAsVec2();
            glm::vec2 delta = (mousePos - m_LastMousePosition) * m_MouseSensitivity;
            m_LastMousePosition = mousePos;

            if (delta.x != 0.0f || delta.y != 0.0f) {
                M_Camera.RotateYaw(-delta.x);
                M_Camera.RotatePitch(-delta.y);
                KE_TAG_LOG_DEBUG("CameraController", "Mouse rotation detected. Delta: ({:.2f}, {:.2f})", delta.x, delta.y);
            }
        }
        if (rotated) {
            KE_TAG_LOG_DEBUG("CameraController", "Rotation detected.");
        }
        // Final step: ensure the camera's internal matrices are updated.
        M_Camera.UpdateMatrices();
    }

    // --- OnEvent (Handles discrete, single-fire events) ---
    void CameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>([this](auto& event) { return this->OnMouseScroll(event); });
        dispatcher.Dispatch<WindowResizeEvent>([this](auto& event) { return this->OnWindowResize(event); });
        dispatcher.Dispatch<KeyReleasedEvent>([this](auto& event) { return this->OnKeyReleased(event); });
    }

    // --- Event Handler Implementations ---

    bool CameraController::OnKeyReleased(KeyReleasedEvent& e)
    {
        switch (e.GetKeyCode())
        {
        case KnightK_V:
        {
            m_MouseRotationEnabled = !m_MouseRotationEnabled;
            if (m_MouseRotationEnabled) {
                m_LastMousePosition = KnightEngine::InputManager::GetMousePositionAsVec2();
                KE_TAG_LOG_DEBUG("CameraController", "Mouse rotation enabled.");
            }
            else {
                KE_TAG_LOG_DEBUG("CameraController", "Mouse rotation disabled.");
            }
            return true; // Event handled
        }
        case KnightK_J: // Increase speed
        {
            M_CameraSpeed *= 1.5f;
            KE_TAG_LOG_DEBUG("CameraController", "Camera speed increased to: {:.2f}", M_CameraSpeed);
            return true;
        }
        case KnightK_K: // Decrease speed
        {
            M_CameraSpeed /= 1.5f;
            if (M_CameraSpeed < 0.1f) M_CameraSpeed = 0.1f;
            KE_TAG_LOG_DEBUG("CameraController", "Camera speed decreased to: {:.2f}", M_CameraSpeed);
            return true;
        }
        case KnightK_U: // Increase sensitivity
        {
            m_MouseSensitivity *= 1.5f;
            KE_TAG_LOG_DEBUG("CameraController", "Mouse sensitivity increased to: {:.3f}", m_MouseSensitivity);
            return true;
        }
        case KnightK_I: // Decrease sensitivity
        {
            m_MouseSensitivity /= 1.5f;
            if (m_MouseSensitivity < 0.01f) m_MouseSensitivity = 0.01f;
            KE_TAG_LOG_DEBUG("CameraController", "Mouse sensitivity decreased to: {:.3f}", m_MouseSensitivity);
            return true;
        }
        case KnightK_C: // NEW: Toggle camera type
        {
            if (M_Camera.GetType() == ECameraType::Perspective)
            {
                M_Camera.SetType(ECameraType::Orthographic);
                // Set some sensible default ortho bounds
                float left = -m_AspectRatio * m_ZoomLevel;
                float right = m_AspectRatio * m_ZoomLevel;
                float bottom = -m_ZoomLevel;
                float top = m_ZoomLevel;
                M_Camera.SetOrthographic(left, right, bottom, top, -1.0f, 1.0f);
                KE_TAG_LOG_INFO("CameraController", "Switched to Orthographic camera.");
            }
            else
            {
                M_Camera.SetType(ECameraType::Perspective);
                // Set some sensible default perspective values
                M_Camera.SetPerspective(45.0f, m_AspectRatio, 0.1f, 1000.0f);
                KE_TAG_LOG_INFO("CameraController", "Switched to Perspective camera.");
            }
            return true;
        }
        }
        return false;
    }

    bool CameraController::OnMouseScroll(MouseScrolledEvent& ms)
    {
        if (M_Camera.GetType() == ECameraType::Orthographic) {
            m_ZoomLevel -= ms.GetYOffset() * 0.25f;
            m_ZoomLevel = std::max(0.25f, m_ZoomLevel);
            M_Camera.SetOrthoBounds(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        }
        else {
            M_Camera.MoveForward(ms.GetYOffset() * -0.5f); // Invert scroll for intuitive zoom
        }
        KE_TAG_LOG_DEBUG("CameraController", "Mouse scrolled: YOffset = {:.2f}", ms.GetYOffset());
        return false;
    }

    bool CameraController::OnWindowResize(WindowResizeEvent& re)
    {
        if (re.GetWidth() == 0 || re.GetHeight() == 0) {
            return false;
        }
        m_AspectRatio = (float)re.GetWidth() / (float)re.GetHeight();
        M_Camera.SetAspectRatio(m_AspectRatio);
        M_Camera.UpdateMatrices();

         
        KE_TAG_LOG_DEBUG("CameraController", "Window resized, new aspect ratio: {:.2f}", m_AspectRatio);
        return false;
    }

} // namespace Knight
