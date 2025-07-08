#include "RenderQueue.hpp"

namespace Knight {
  

    void RenderQueue::AddCommand(const RenderCommand& command)
    {
        m_RenderCommands.push_back(command);
    }

    void RenderQueue::ClearCommands()
    {
       
    }
}