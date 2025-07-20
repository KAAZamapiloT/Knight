#include "CameraController.hpp"
#include "input/InputManager.h"
#include "KeyCodes.h"
#include "Event/EventDispatcher.hpp"
#include "Event/MouseEvent.hpp"
#include "Event/WindowEvent.hpp"
#include "Event/KeyEvent.hpp" // Make sure this is included for KeyReleasedEvent
#include <glm/trigonometric.hpp>
#include <algorithm> // For std::max

namespace Knight {

    CameraController::CameraController(float aspectRatio, ECameraType type)
        : m_AspectRatio(aspectRatio)
    {
        if (type == ECameraType::Perspective) {
            // Use the perspective constructor
            M_Camera = Camera(45.0f, m_AspectRatio, 0.1f, 1000.0f);
            M_Camera.SetPosition({ 0.0f, 0.0f, 5.0f }); // Start back a bit to see the origin
        }
        else { // Orthographic
            // Calculate ortho bounds based on aspect ratio and a default zoom
            float left = -m_AspectRatio * m_ZoomLevel;
            float right = m_AspectRatio * m_ZoomLevel;
            float bottom = -m_ZoomLevel;
            float top = m_ZoomLevel;
            M_Camera = Camera(left, right, bottom, top, -1.0f, 1.0f);
        }
    }

    void CameraController::OnUpdate(KnightEngine::TimeStamp ts)
    {
        // Calculate a consistent speed based on the frame time
        const float speed = M_CameraSpeed * ts;
        const float rotationSpeed = M_CameraRotationSpeed * ts;

        // --- Handle Camera Movement ---
        if (M_Camera.GetType() == ECameraType::Perspective) {
            // Perspective: Use camera's local axes for FPS-style movement
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_W, 0)) {
                M_Camera.MoveForward(speed);
            }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_S, 0)) {
                M_Camera.MoveForward(-speed);
            }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_A, 0)) {
                M_Camera.MoveRight(-speed);
            }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_D, 0)) {
                M_Camera.MoveRight(speed);
            }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_E, 0)) {
                M_Camera.MoveUp(speed);
            }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_Q, 0)) {
                M_Camera.MoveUp(-speed);
            }
        }
        else {
            // Orthographic: Use world axes for 2D-style movement
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_W, 0)) {
                M_Camera.SetPosition(M_Camera.GetPosition() + glm::vec3(0.0f, speed, 0.0f));
            }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_S, 0)) {
                M_Camera.SetPosition(M_Camera.GetPosition() + glm::vec3(0.0f, -speed, 0.0f));
            }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_A, 0)) {
                M_Camera.SetPosition(M_Camera.GetPosition() + glm::vec3(-speed, 0.0f, 0.0f));
            }
            if (KnightEngine::InputManager::IsKeyPressed(KnightK_D, 0)) {
                M_Camera.SetPosition(M_Camera.GetPosition() + glm::vec3(speed, 0.0f, 0.0f));
            }
        }

        // --- Handle Camera Rotation (Perspective Only) ---
        if (M_Camera.GetType() == ECameraType::Perspective) {
            if (m_MouseRotationEnabled) {
                // Use mouse movement for rotation
                glm::vec2 mousePos = KnightEngine::InputManager::GetMousePositionAsVec2(); // Assuming this now returns glm::vec2
                glm::vec2 delta = (mousePos - m_LastMousePosition) * m_MouseSensitivity;
                m_LastMousePosition = mousePos;

                if (delta.x != 0.0f || delta.y != 0.0f) {
                    // Invert delta.x for yaw to feel natural (moving mouse right turns right)
                    // Invert delta.y for pitch (moving mouse up looks up)
                    M_Camera.RotateYaw(-delta.x);
                    M_Camera.RotatePitch(-delta.y);
                }
            }
            else {
                // Use arrow keys for rotation
                if (KnightEngine::InputManager::IsKeyPressed(KnightK_UP, 0)) {
                    M_Camera.RotatePitch(rotationSpeed);
                }
                if (KnightEngine::InputManager::IsKeyPressed(KnightK_DOWN, 0)) {
                    M_Camera.RotatePitch(-rotationSpeed);
                }
                if (KnightEngine::InputManager::IsKeyPressed(KnightK_LEFT, 0)) {
                    M_Camera.RotateYaw(rotationSpeed);
                }
                if (KnightEngine::InputManager::IsKeyPressed(KnightK_RIGHT, 0)) {
                    M_Camera.RotateYaw(-rotationSpeed);
                }
            }
        }

        // IMPORTANT: After all modifications, update the camera's matrices.
        M_Camera.UpdateMatrices();
    }

    void CameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(KNIGHT_BIND_FN(CameraController::OnMouseScroll));
        dispatcher.Dispatch<WindowResizeEvent>(KNIGHT_BIND_FN(CameraController::OnWindowResize));
        dispatcher.Dispatch<KeyReleasedEvent>(KNIGHT_BIND_FN(CameraController::OnKeyReleased)); // Dispatch key releases
    }

    bool CameraController::OnKeyReleased(KeyReleasedEvent& e)
    {
        if (e.GetKeyCode() == KnightK_V) {
            m_MouseRotationEnabled = !m_MouseRotationEnabled;
            if (m_MouseRotationEnabled) {
                // When enabling, capture the current mouse position to prevent a large jump on the next frame
                m_LastMousePosition = KnightEngine::InputManager::GetMousePositionAsVec2();
            }
            return true; // Event handled
        }
        return false;
    }

    bool CameraController::OnMouseScroll(MouseScrolledEvent& ms)
    {
        // Only handle zoom for orthographic camera
        if (M_Camera.GetType() == ECameraType::Orthographic) {
            m_ZoomLevel -= ms.GetYOffset() * 0.25f;
            m_ZoomLevel = std::max(0.25f, m_ZoomLevel); // Prevent zooming in too far

            // Recalculate ortho bounds based on new zoom
            float left = -m_AspectRatio * m_ZoomLevel;
            float right = m_AspectRatio * m_ZoomLevel;
            float bottom = -m_ZoomLevel;
            float top = m_ZoomLevel;
            M_Camera.SetOrthoBounds(left, right, bottom, top);
        }
        else {
            // For perspective, we can move forward/backward
            M_Camera.MoveForward(ms.GetYOffset() * 0.5f);
        }
        return false;
    }

    bool CameraController::OnWindowResize(WindowResizeEvent& re)
    {
        if (re.GetWidth() == 0 || re.GetHeight() == 0) {
            return false;
        }

        m_AspectRatio = (float)re.GetWidth() / (float)re.GetHeight();
        M_Camera.SetAspectRatio(m_AspectRatio);

        // Also update ortho bounds if it's an ortho camera
        if (M_Camera.GetType() == ECameraType::Orthographic) {
            float left = -m_AspectRatio * m_ZoomLevel;
            float right = m_AspectRatio * m_ZoomLevel;
            float bottom = -m_ZoomLevel;
            float top = m_ZoomLevel;
            M_Camera.SetOrthoBounds(left, right, bottom, top);
        }
        return false;
    }

} // namespace Knight
