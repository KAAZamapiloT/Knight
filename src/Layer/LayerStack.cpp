#include "LayerStack.hpp"

KnightEngine::LayerStack::LayerStack()
{
	
}

KnightEngine::LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers)
	{
		delete layer; // Clean up the layers
	}
	m_Layers.clear();

}

void KnightEngine::LayerStack::PushLayer(Layer* layer)
{
	m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
}

void KnightEngine::LayerStack::PushOverlay(Layer* overlay)
{
	m_Layers.emplace_back(overlay);
}

void KnightEngine::LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
	if (it != m_Layers.end()) {
		m_Layers.erase(it);
		--m_LayerInsertIndex; // Adjust the insert iterator if necessary
	}
}

void KnightEngine::LayerStack::PopOverlay(Layer* overlay)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
	if (it != m_Layers.end()) {
		m_Layers.erase(it);
		
	}
}
