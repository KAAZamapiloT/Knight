#include "WindowsInput.hpp"
#include "SDL3/SDL.h"
#include "Core/Application.hpp"

namespace KnightEngine
{
	// Static instance initializationsda
	InputManager* InputManager::s_Instance = new WindowsInput();
    
}


bool KnightEngine::WindowsInput::IsKeyPressedImpl(int button,int mod)
{
    int numKeys;
    const bool* state = SDL_GetKeyboardState(&numKeys);

    // Convert keycode to scancode (only takes keycode, not modifiers)
    SDL_Scancode scancode = SDL_GetScancodeFromKey(button,Knight_TO_SDL_MOD(mod));

    // Check if scancode is valid and within bounds
    if (scancode < 0 || scancode >= numKeys)
        return false;

    // Check if the key is pressed
    bool keyPressed = state[scancode];

    // If no modifiers are required, just return key state
    if (mod == 0)
        return keyPressed;

    // If modifiers are required, check them separately
    if (keyPressed)
    {
        // Get current modifier state
        SDL_Keymod currentMods = SDL_GetModState();
        SDL_Keymod* requiredMods = Knight_TO_SDL_MOD(mod);

        // Check if all required modifiers are pressed
        return (currentMods & *requiredMods) == *requiredMods;
    }

    return false;
}

bool KnightEngine::WindowsInput::IsMouseButtonPressedImpl(int button)
{
    // Get current mouse state
    Uint32 mouseState = SDL_GetMouseState(NULL, NULL);

    // Check if the specified mouse button is pressed
    return (mouseState & SDL_BUTTON_MASK(button)) != 0;
}

// Alternative implementation if you also want to get mouse position
bool KnightEngine::WindowsInput::IsMouseButtonPressedImpl_WithPosition(int button, float* x, float* y)
{
    float mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    // Set position if pointers are provided
    if (x) *x = mouseX;
    if (y) *y = mouseY;

    // Check if the specified mouse button is pressed
    return (mouseState & SDL_BUTTON_MASK(button)) != 0;
}

// Convenience functions for specific mouse buttons
bool KnightEngine::WindowsInput::IsLeftMouseButtonPressed()
{
    return IsMouseButtonPressedImpl(SDL_BUTTON_LEFT);
}

bool KnightEngine::WindowsInput::IsRightMouseButtonPressed()
{
    return IsMouseButtonPressedImpl(SDL_BUTTON_RIGHT);
}

bool KnightEngine::WindowsInput::IsMiddleMouseButtonPressed()
{
    return IsMouseButtonPressedImpl(SDL_BUTTON_MIDDLE);
}

SDL_Keymod* KnightEngine::WindowsInput::Knight_TO_SDL_MOD(int mod)
{
   
        // Static variable to store the result (persists between function calls)
        static SDL_Keymod result;

        // Reset the result
        result = SDL_KMOD_NONE;

        // Define your engine's modifier bit flags
        const int KNIGHT_MOD_LSHIFT = 0x0001;
        const int KNIGHT_MOD_RSHIFT = 0x0002;
        const int KNIGHT_MOD_LCTRL = 0x0040;
        const int KNIGHT_MOD_RCTRL = 0x0080;
        const int KNIGHT_MOD_LALT = 0x0100;
        const int KNIGHT_MOD_RALT = 0x0200;
        const int KNIGHT_MOD_LGUI = 0x0400;
        const int KNIGHT_MOD_RGUI = 0x0800;
        const int KNIGHT_MOD_NUM = 0x1000;
        const int KNIGHT_MOD_CAPS = 0x2000;
        const int KNIGHT_MOD_MODE = 0x4000;
        const int KNIGHT_MOD_SCROLL = 0x8000;

        // Convert bit flags to SDL key modifiers
        if (mod & KNIGHT_MOD_LSHIFT) result |= SDL_KMOD_LSHIFT;
        if (mod & KNIGHT_MOD_RSHIFT) result |= SDL_KMOD_RSHIFT;
        if (mod & KNIGHT_MOD_LCTRL)  result |= SDL_KMOD_LCTRL;
        if (mod & KNIGHT_MOD_RCTRL)  result |= SDL_KMOD_RCTRL;
        if (mod & KNIGHT_MOD_LALT)   result |= SDL_KMOD_LALT;
        if (mod & KNIGHT_MOD_RALT)   result |= SDL_KMOD_RALT;
        if (mod & KNIGHT_MOD_LGUI)   result |= SDL_KMOD_LGUI;
        if (mod & KNIGHT_MOD_RGUI)   result |= SDL_KMOD_RGUI;
        if (mod & KNIGHT_MOD_NUM)    result |= SDL_KMOD_NUM;
        if (mod & KNIGHT_MOD_CAPS)   result |= SDL_KMOD_CAPS;
        if (mod & KNIGHT_MOD_MODE)   result |= SDL_KMOD_MODE;
        if (mod & KNIGHT_MOD_SCROLL) result |= SDL_KMOD_SCROLL;

        return &result;
    

}
