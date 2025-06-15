#pragma once
#include "EngineApi.hpp"
namespace KnightEngine {
    class KNIGHT_ENGINE_API Window
    {
    public:
        virtual ~Window() = default;

        virtual bool PollEvents() = 0;
        virtual void SwapBuffers() = 0;
        virtual void* GetNativeWindow() = 0;
        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;
        virtual void Shutdown() = 0;
    };
}
