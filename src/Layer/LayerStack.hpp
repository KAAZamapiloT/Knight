#pragma once
#include"EngineApi.hpp"
#include"Engine.hpp"
#include"Layer/Layer.hpp"
namespace KnightEngine
{
	class KNIGHT_ENGINE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		void PushLayer(Layer* layer); ///< Push a layer onto the stack.
		void PushOverlay(Layer* overlay); ///< Push an overlay layer onto the stack.
		void PopLayer(Layer* layer); ///< Pop a layer from the stack.
		void PopOverlay(Layer* overlay); ///< Pop an overlay layer from the stack.
		inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); } ///< Returns an iterator to the beginning of the layer stack.
		inline std::vector<Layer*>::iterator end() { return m_Layers.end(); } ///< Returns an iterator to the end of the layer stack.
	private:
		std::vector<Layer*> m_Layers; ///< The vector containing all layers in the stack.
		std::vector<Layer*>::iterator m_LayerInsert; ///< Iterator to the beginning of the overlay layers in the stack.
		
	};
}


