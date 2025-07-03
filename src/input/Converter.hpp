#pragma once
#include "SDL3/SDL.h"

/// <summary>
/// Knight Engine Keys MOds to SDL mods
/// </summary>
/// <param name="int Mods"></param>
/// <returns>SDL_KEYMODE</returns>
SDL_Keymod* K_TO_E(int mod)
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