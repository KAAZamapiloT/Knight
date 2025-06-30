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
	if (layer == nullptr) return; // Check for null pointer
	m_Layers.emplace(m_LayerInsert, layer); // Insert the layer at the current insert position
	
}

void KnightEngine::LayerStack::PushOverlay(Layer* overlay)
{
}

void KnightEngine::LayerStack::PopLayer(Layer* layer)
{
}

void KnightEngine::LayerStack::PopOverlay(Layer* overlay)
{
}
