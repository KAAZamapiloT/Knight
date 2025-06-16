#pragma once
#include"Engine.hpp"
#include"EngineApi.hpp"
#include<Event/Event.hpp>
namespace KnightEngine {
    class KNIGHT_ENGINE_API EventQueue {
    public:
        void Push(std::shared_ptr<Event> e) {
            m_Queue.push(e);
        }

        std::shared_ptr<Event> Pop() {
            if (m_Queue.empty()) return nullptr;
            auto e = m_Queue.front();
            m_Queue.pop();
            return e;
        }
		size_t Size() const { return m_Queue.size(); }
        bool IsEmpty() const { return m_Queue.empty(); }

    private:
        std::queue<std::shared_ptr<Event>> m_Queue;
    };


    class KNIGHT_ENGINE_API EventQueueListner {
    public:
        ///void PushEvents(Event& E);
        void DispatchEvents();
	private:
		EventQueue m_EventQueue;
		EventQueue m_HighPriorityQueue;

    };
}



