#include "Layer.hpp"

KnightEngine::Layer::~Layer()
{
	KE_TAG_LOG_WARN("LAYER", "DESTROYED",m_DebugName);
}
