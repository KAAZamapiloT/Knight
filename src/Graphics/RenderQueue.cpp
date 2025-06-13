#include "RenderQueue.hpp"

namespace Knight {
  

    void RenderQueue::AddCommand(const RenderCommand& command)
    {

    }

    void RenderQueue::ClearCommands()
    {
		m_RenderCommands->clear();
    }
}