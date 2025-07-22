#pragma once
#include"KnightEnginepch.h"
#include"EngineApi.hpp"
#include"Graphics/Camera.hpp"
#include"Core/Time.hpp"
#include"Event/ApplicationEvents.hpp"
#include"Event/MouseEvent.hpp"
#include"Event/EventDispatcher.hpp"
#include"utils/Math.hpp"
namespace Knight {
	class KNIGHT_ENGINE_API CameraController {
	public:
		CameraController(float AspectRatio,ECameraType E);  // CAMREA WOULD REUIRE A ZOOM AND OTHER THINGS
		CameraController() = default;
		void OnUpdate(KnightEngine::TimeStamp ts);
		void OnEvent(Event& e);
		Camera& GetCamera() { return M_Camera; }
		const Camera& GetCamera() const { return M_Camera; }
	private:
		bool OnMouseScroll(MouseScrolledEvent& ms);
		bool OnWindowResize(WindowResizeEvent& re);
		bool OnKeyReleased(KeyReleasedEvent&KE);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		Camera M_Camera;

		float M_CameraSpeed = 0.1f;
		float M_CameraRotationSpeed = 0.1f;
		bool m_MouseRotationEnabled = false;
		glm::vec2 m_LastMousePosition;
		float m_MouseSensitivity=0.001f;
	};
}


// THIS CLASS IS GOING TO BE A VIEWPORT TYPE CAMERA