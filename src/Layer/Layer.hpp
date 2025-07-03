#pragma once
#include"EngineApi.hpp"
#include"Core/Logger.hpp"
#include"KnightEnginepch.h"
#include"Event/Event.hpp"
namespace KnightEngine {
	class KNIGHT_ENGINE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer")
			: m_DebugName(name) {
			KE_TAG_LOG_INFO("Layer", "Layer created: {}", m_DebugName);
		}
		virtual ~Layer();

		virtual void OnAttach() {

		} ///< Called when the layer is attached to the application.

		virtual void OnDetach() {
		} ///< Called when the layer is detached from the application.
		virtual void OnUpdate() {
		} ///< Called every frame to update the layer.
		virtual void OnEvent(Event&event) {

		}
		inline const std::string& GetName() const {
			return m_DebugName;
		} ///< Returns the name of the layer.
	private:
		std::string m_DebugName; ///< The name of the layer, used for debugging and logging.
	};
}


