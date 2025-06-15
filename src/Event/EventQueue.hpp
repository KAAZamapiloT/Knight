#pragma once
#include"Engine.hpp"
#include"EngineApi.hpp"
#include<Event/Event.hpp>
namespace KnightEngine {
    class EventQueue {
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

        bool IsEmpty() const { return m_Queue.empty(); }

    private:
        std::queue<std::shared_ptr<Event>> m_Queue;
    };


    class KNIGHT_ENGINE_API EventQueueListner {
    public:
        void PollEvents(Event& E);
	private:
		EventQueue m_EventQueue;
		EventQueue m_HighPriorityQueue;

    };
}



