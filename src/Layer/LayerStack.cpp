#include "LayerStack.hpp"

KnightEngine::LayerStack::LayerStack()
{
	m_LayerInsert = m_Layers.begin();
}

KnightEngine::LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers)
	{
		delete layer; // Clean up the layers
	}
	m_Layers.clear();
	m_LayerInsert = m_Layers.begin(); // Reset the insert iterator
}

void KnightEngine::LayerStack::PushLayer(Layer* layer)
{
	m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
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
		--m_LayerInsert; // Adjust the insert iterator if necessary
	}
}

void KnightEngine::LayerStack::PopOverlay(Layer* overlay)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
	if (it != m_Layers.end()) {
		m_Layers.erase(it);
		
	}
}
