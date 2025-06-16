#include "EventQueue.hpp"
#include "Event/EventBus.hpp"
/*void KnightEngine::EventQueueListner::PushEvents(Event& E)
{
	if(E.blocking)
		m_HighPriorityQueue.Push(std::make_shared<Event>(E));
	else
	    m_EventQueue.Push(std::make_shared<Event>(E));
}
*/
void KnightEngine::EventQueueListner::DispatchEvents()
{
	if (!m_HighPriorityQueue.IsEmpty())
	{
		
	}
	else if (!m_EventQueue.IsEmpty())
	{
		
	}
}
