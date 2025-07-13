#include "InputManager.h"
#include "platform/WINDOWS/WindowsInput.hpp"

namespace KnightEngine {
    InputManager* InputManager::s_Instance = nullptr;

    InputManager* InputManager::GetInstance() {
        if (!s_Instance) {
            s_Instance = new WindowsInput();
        }
        return s_Instance;
    }
}
