#pragma once
#include"spdlog/logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include<string>
#include <utility> 
#include "EngineApi.hpp"
#include <cassert>
#include <cstdlib>

/**
 * @enum LogLevel
 * @brief Defines different levels of logging severity.
 */
enum LogLevel
{
    CRITICAL, ///< Critical errors that cause the application to crash or become unusable.
    INFO,     ///< Informational messages that provide general information about the application's state.
    WARN,     ///< Warnings that indicate potential issues but do not stop the application from running.
    DEBUG,
    TRACE
};

/**
 * @class Logger
 * @brief Static logger utility using spdlog for KnightEngine.
 *
 * Provides convenient macros and static methods for logging messages across different log levels.
 * In release builds, logging can be disabled for performance.
 */
class KNIGHT_ENGINE_API Logger {
public:
    /**
   * @brief Logs a message with the specified log level.
   *
   * @tparam Args Variadic template for formatting arguments.
   * @param level Logging severity (CRITICAL, INFO, etc.)
   * @param format printf-style format string.
   * @param args Arguments to be formatted into the string.
   */
    template<typename... Args>
    static void Log(LogLevel level, const char* format, Args&&... args)
    {
        switch (level) {
        case CRITICAL:
            spdlog::critical(format, std::forward<Args>(args)...);
            break;
        case INFO:
            spdlog::info(format, std::forward<Args>(args)...);
            break;
        case WARN:
            spdlog::warn(format, std::forward<Args>(args)...);
            break;
        case DEBUG:
            spdlog::debug(format, std::forward<Args>(args)...);
            break;
        case TRACE:
            spdlog::trace(format, std::forward<Args>(args)...);
            break;
        default:
            spdlog::info(format, std::forward<Args>(args)...);
            break;
        }
    }

    /**
    * @brief Logs a message with a custom tag.
    *
    * Useful for subsystems or scoped messages.
    *
    * @tparam Args Variadic formatting arguments.
    * @param tag Tag to prepend to the log message (e.g., "Renderer").
    * @param level Logging severity.
    * @param fmt printf-style format string.
    * @param args Formatting arguments.
    */
    template<typename... Args>
    static void C_LOG(const std::string tag, LogLevel level, const char* fmt, Args&&... args) {
        std::string tagged_fmt = "[" + tag + "] " + fmt;
        Log(level, tagged_fmt.c_str(), std::forward<Args>(args)...);
    }

    /**
    * @brief No-op logging function used in release builds.
    *
    * Avoids compiling in logs in production mode.
    *
    * @tparam Args Variadic formatting arguments.
    * @param level Logging severity.
    * @param format printf-style format string.
    * @param args Formatting arguments.
    */
    template<typename... Args>
    static void NLog(LogLevel level, const char* format, Args&&... args) {
        // No-op in release builds
    }

    /**
    * @brief No-op custom-tagged logging function used in release builds.
    *
    * @tparam Args Variadic formatting arguments.
    * @param tag Log tag (e.g., "Renderer", "Input").
    * @param level Logging severity.
    * @param fmt printf-style format string.
    * @param args Formatting arguments.
    */
    template<typename... Args>
    static void NC_LOG(const std::string tag, LogLevel level, const char* fmt, Args&&... args) {
        // No-op in release builds
    }

    /**
    * @brief Logs an assertion failure and terminates the program.
    *
    * @tparam Args Variadic formatting arguments.
    * @param condition_str String representation of the failed condition.
    * @param file Source file where assertion failed.
    * @param line Line number where assertion failed.
    * @param message Custom error message.
    * @param args Formatting arguments for the message.
    */
    template<typename... Args>
    static void LogAssertionFailure(const char* condition_str, const char* file, int line, const char* message, Args&&... args) {
        std::string full_message = std::string("Assertion failed: ") + condition_str +
            " at " + file + ":" + std::to_string(line) + " - " + message;
        spdlog::critical(full_message, std::forward<Args>(args)...);
        spdlog::shutdown(); // Ensure logs are flushed before termination
        std::abort();
    }

    /**
    * @brief Logs a tagged assertion failure and terminates the program.
    *
    * @tparam Args Variadic formatting arguments.
    * @param tag Custom tag for the assertion.
    * @param condition_str String representation of the failed condition.
    * @param file Source file where assertion failed.
    * @param line Line number where assertion failed.
    * @param message Custom error message.
    * @param args Formatting arguments for the message.
    */
    template<typename... Args>
    static void LogTaggedAssertionFailure(const std::string& tag, const char* condition_str, const char* file, int line, const char* message, Args&&... args) {
        std::string full_message = std::string("[") + tag + "] Assertion failed: " + condition_str +
            " at " + file + ":" + std::to_string(line) + " - " + message;
        spdlog::critical(full_message, std::forward<Args>(args)...);
        spdlog::shutdown(); // Ensure logs are flushed before termination
        std::abort();
    }

    /**
    * @brief No-op assertion failure function for release builds.
    */
    template<typename... Args>
    static void NLogAssertionFailure(const char* condition_str, const char* file, int line, const char* message, Args&&... args) {
        // No-op in release builds
    }

    /**
    * @brief No-op tagged assertion failure function for release builds.
    */
    template<typename... Args>
    static void NLogTaggedAssertionFailure(const std::string& tag, const char* condition_str, const char* file, int line, const char* message, Args&&... args) {
        // No-op in release builds
    }
};

//  Logging macros: disabled in Release, enabled in Debug
#if defined(_DEBUG) || !defined(NDEBUG)
#define KE_LOG_INFO(...)     Logger::Log(INFO, __VA_ARGS__)
#define KE_LOG_WARN(...)     Logger::Log(WARN, __VA_ARGS__)
#define KE_LOG_DEBUG(...)    Logger::Log(DEBUG, __VA_ARGS__)
#define KE_LOG_CRITICAL(...) Logger::Log(CRITICAL, __VA_ARGS__)
#define KE_LOG_TRACE(...)    Logger::Log(TRACE, __VA_ARGS__)
#define KE_TAG_LOG_INFO(tag, ...)    Logger::C_LOG(tag, INFO, __VA_ARGS__)
#define KE_TAG_LOG_WARN(tag, ...)    Logger::C_LOG(tag, WARN, __VA_ARGS__)
#define KE_TAG_LOG_DEBUG(tag, ...)   Logger::C_LOG(tag, DEBUG, __VA_ARGS__)
#define KE_TAG_LOG_CRITICAL(tag, ...) Logger::C_LOG(tag, CRITICAL, __VA_ARGS__)
#define KE_TAG_LOG_TRACE(tag, ...)   Logger::C_LOG(tag, TRACE, __VA_ARGS__)

// Assertion macros - enabled in debug builds
#define KE_ASSERT(condition, ...) \
    do { \
        if (!(condition)) { \
            Logger::LogAssertionFailure(#condition, __FILE__, __LINE__, __VA_ARGS__); \
        } \
    } while(0)

#define KE_CORE_ASSERT(condition, ...) \
    do { \
        if (!(condition)) { \
            Logger::LogAssertionFailure(#condition, __FILE__, __LINE__, __VA_ARGS__); \
        } \
    } while(0)

#define KE_TAG_ASSERT(tag, condition, ...) \
    do { \
        if (!(condition)) { \
            Logger::LogTaggedAssertionFailure(tag, #condition, __FILE__, __LINE__, __VA_ARGS__); \
        } \
    } while(0)

// Verify macros - these always execute the condition but only assert in debug
#define KE_VERIFY(condition, ...) \
    do { \
        if (!(condition)) { \
            Logger::LogAssertionFailure(#condition, __FILE__, __LINE__, __VA_ARGS__); \
        } \
    } while(0)

#define KE_TAG_VERIFY(tag, condition, ...) \
    do { \
        if (!(condition)) { \
            Logger::LogTaggedAssertionFailure(tag, #condition, __FILE__, __LINE__, __VA_ARGS__); \
        } \
    } while(0)

#else
    // No-ops in release builds
#define KE_LOG_INFO(...)     Logger::NLog(INFO, __VA_ARGS__)
#define KE_LOG_WARN(...)     Logger::NLog(WARN, __VA_ARGS__)
#define KE_LOG_DEBUG(...)    Logger::NLog(DEBUG, __VA_ARGS__)
#define KE_LOG_CRITICAL(...) Logger::NLog(CRITICAL, __VA_ARGS__)
#define KE_LOG_TRACE(...)    Logger::NLog(TRACE, __VA_ARGS__)

#define KE_TAG_LOG_INFO(tag, ...)    Logger::NC_LOG(tag, INFO, __VA_ARGS__)
#define KE_TAG_LOG_WARN(tag, ...)    Logger::NC_LOG(tag, WARN, __VA_ARGS__)
#define KE_TAG_LOG_DEBUG(tag, ...)   Logger::NC_LOG(tag, DEBUG, __VA_ARGS__)
#define KE_TAG_LOG_CRITICAL(tag, ...) Logger::NC_LOG(tag, CRITICAL, __VA_ARGS__)
#define KE_TAG_LOG_TRACE(tag, ...)   Logger::NC_LOG(tag, TRACE, __VA_ARGS__)

// Assertion macros - disabled in release builds
#define KE_ASSERT(condition, ...) \
    do { \
        (void)(condition); \
        Logger::NLogAssertionFailure(#condition, __FILE__, __LINE__, __VA_ARGS__); \
    } while(0)

#define KE_CORE_ASSERT(condition, ...) \
    do { \
        (void)(condition); \
        Logger::NLogAssertionFailure(#condition, __FILE__, __LINE__, __VA_ARGS__); \
    } while(0)

#define KE_TAG_ASSERT(tag, condition, ...) \
    do { \
        (void)(condition); \
        Logger::NLogTaggedAssertionFailure(tag, #condition, __FILE__, __LINE__, __VA_ARGS__); \
    } while(0)

// Verify macros - always execute the condition, but don't assert in release
#define KE_VERIFY(condition, ...) \
    do { \
        (void)(condition); \
    } while(0)

#define KE_TAG_VERIFY(tag, condition, ...) \
    do { \
        (void)(condition); \
    } while(0)

#endif

/**
 * @def KE_ASSERT(condition, message, ...)
 * @brief Asserts a condition in debug builds only.
 * @details If the condition is false, logs the assertion failure and terminates the program.
 * In release builds, this becomes a no-op.
 *
 * @param condition The condition to check
 * @param message Format string for the error message
 * @param ... Format arguments
 *
 * @def KE_CORE_ASSERT(condition, message, ...)
 * @brief Core engine assertion - same as KE_ASSERT but semantically different.
 * @details Use this for core engine assertions vs application-level assertions.
 *
 * @def KE_TAG_ASSERT(tag, condition, message, ...)
 * @brief Tagged assertion with custom subsystem identifier.
 * @details Useful for identifying which subsystem triggered the assertion.
 *
 * @def KE_VERIFY(condition, message, ...)
 * @brief Verify macro that always executes the condition.
 * @details Unlike ASSERT, this executes the condition in both debug and release builds,
 * but only performs the assertion check in debug builds.
 *
 * @def KE_TAG_VERIFY(tag, condition, message, ...)
 * @brief Tagged verify macro with custom subsystem identifier.
 *
 * @example
 * KE_ASSERT(ptr != nullptr, "Pointer cannot be null");
 * KE_TAG_ASSERT("Renderer", texture.IsValid(), "Invalid texture: {}", texture.GetName());
 * KE_VERIFY(InitializeSystem(), "Failed to initialize system");
 */