#include "RenderQueue.hpp"

namespace Knight {
    RenderCommand* RenderQueue::DispatchCommand()
    {
        return nullptr;
    }

    void RenderQueue::AddCommand(const RenderCommand& command)
    {

    }

    void RenderQueue::ClearCommands()
    {
		m_RenderCommands->clear();
    }
}