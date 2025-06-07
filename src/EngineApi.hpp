#pragma once

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
#define KNIGHT_PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
#define KNIGHT_PLATFORM_MACOS
#elif defined(__linux__)
#define KNIGHT_PLATFORM_LINUX
#else
#error "Unsupported platform!"
#endif

// Export/import macros
#if defined(KNIGHT_PLATFORM_WINDOWS)
#if defined(KNIGHT_ENGINE_BUILD_DLL)
    // Building DLL
#define KNIGHT_ENGINE_API __declspec(dllexport)
#elif defined(KNIGHT_ENGINE_USE_DLL)
    // Using DLL
#define KNIGHT_ENGINE_API __declspec(dllimport)
#else
    // Building/using EXE — no import/export needed
#define KNIGHT_ENGINE_API
#endif

#elif defined(KNIGHT_PLATFORM_LINUX) || defined(KNIGHT_PLATFORM_MACOS)
#if defined(KNIGHT_ENGINE_BUILD_DLL)
#define KNIGHT_ENGINE_API __attribute__((visibility("default")))
#else
#define KNIGHT_ENGINE_API
#endif

#else
#define KNIGHT_ENGINE_API
#endif
