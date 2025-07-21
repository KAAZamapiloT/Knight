#pragma once
#include "EngineApi.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <string>
#include <utility>
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
    DEBUG,    ///< Detailed debug information.
    TRACE     ///< Highly detailed trace information for diagnosing issues.
};

/**
 * @class Logger
 * @brief Static logger utility using spdlog for KnightEngine.
 */
class KNIGHT_ENGINE_API Logger {
public:
    /**
    * @brief Logs a message with the specified log level.
    */
    template<typename... Args>
    static void Log(LogLevel level, spdlog::format_string_t<Args...> format, Args&&... args)
    {
        switch (level) {
        case CRITICAL: spdlog::critical(format, std::forward<Args>(args)...); break;
        case INFO:     spdlog::info(format, std::forward<Args>(args)...); break;
        case WARN:     spdlog::warn(format, std::forward<Args>(args)...); break;
        case DEBUG:    spdlog::debug(format, std::forward<Args>(args)...); break;
        case TRACE:    spdlog::trace(format, std::forward<Args>(args)...); break;
        default:       spdlog::info(format, std::forward<Args>(args)...); break;
        }
    }

    /**
    * @brief Logs a message with a custom tag.
    */
    template<typename... Args>
    static void C_LOG(const std::string& tag, LogLevel level, const std::string& fmt, Args&&... args) {
        std::string tagged_fmt = "[" + tag + "] " + fmt;
        // Use fmt::runtime for dynamically created format strings
        switch (level) {
        case CRITICAL: spdlog::critical(fmt::runtime(tagged_fmt), std::forward<Args>(args)...); break;
        case INFO:     spdlog::info(fmt::runtime(tagged_fmt), std::forward<Args>(args)...); break;
        case WARN:     spdlog::warn(fmt::runtime(tagged_fmt), std::forward<Args>(args)...); break;
        case DEBUG:    spdlog::debug(fmt::runtime(tagged_fmt), std::forward<Args>(args)...); break;
        case TRACE:    spdlog::trace(fmt::runtime(tagged_fmt), std::forward<Args>(args)...); break;
        default:       spdlog::info(fmt::runtime(tagged_fmt), std::forward<Args>(args)...); break;
        }
    }

    /**
    * @brief Alternative C_LOG implementation using string_view (more efficient)
    */
    template<typename... Args>
    static void C_LOG_ALT(const std::string& tag, LogLevel level, std::string_view fmt, Args&&... args) {
        std::string tagged_fmt = "[" + tag + "] " + std::string(fmt);
        switch (level) {
        case CRITICAL: spdlog::critical(fmt::runtime(tagged_fmt), std::forward<Args>(args)...); break;
        case INFO:     spdlog::info(fmt::runtime(tagged_fmt), std::forward<Args>(args)...); break;
        case WARN:     spdlog::warn(fmt::runtime(tagged_fmt), std::forward<Args>(args)...); break;
        case DEBUG:    spdlog::debug(fmt::runtime(tagged_fmt), std::forward<Args>(args)...); break;
        case TRACE:    spdlog::trace(fmt::runtime(tagged_fmt), std::forward<Args>(args)...); break;
        default:       spdlog::info(fmt::runtime(tagged_fmt), std::forward<Args>(args)...); break;
        }
    }

    /**
    * @brief Logs an assertion failure (with format arguments) and terminates.
    */
    template<typename... Args>
    static void LogAssertionFailure(const char* condition_str, const char* file, int line, const char* message, Args&&... args) {
        std::string user_message = fmt::format(fmt::runtime(message), std::forward<Args>(args)...);
        spdlog::critical("Assertion failed: {} at {}:{} - {}", condition_str, file, line, user_message);
        spdlog::shutdown();
        std::abort();
    }

    /**
    * @brief Overload for assertion failures with no format arguments.
    */
    static void LogAssertionFailure(const char* condition_str, const char* file, int line, const char* message) {
        spdlog::critical("Assertion failed: {} at {}:{} - {}", condition_str, file, line, message);
        spdlog::shutdown();
        std::abort();
    }

    /**
    * @brief Logs a tagged assertion failure (with format arguments) and terminates.
    */
    template<typename... Args>
    static void LogTaggedAssertionFailure(const std::string& tag, const char* condition_str, const char* file, int line, const char* message, Args&&... args) {
        std::string user_message = fmt::format(fmt::runtime(message), std::forward<Args>(args)...);
        spdlog::critical("[{}] Assertion failed: {} at {}:{} - {}", tag, condition_str, file, line, user_message);
        spdlog::shutdown();
        std::abort();
    }

    /**
    * @brief Overload for tagged assertion failures with no format arguments.
    */
    static void LogTaggedAssertionFailure(const std::string& tag, const char* condition_str, const char* file, int line, const char* message) {
        spdlog::critical("[{}] Assertion failed: {} at {}:{} - {}", tag, condition_str, file, line, message);
        spdlog::shutdown();
        std::abort();
    }
};

// In release builds, all logging macros compile to nothing.
#if defined(_DEBUG) || !defined(NDEBUG)
#define KE_LOG_INFO(...)         Logger::Log(INFO, __VA_ARGS__)
#define KE_LOG_WARN(...)         Logger::Log(WARN, __VA_ARGS__)
#define KE_LOG_DEBUG(...)        Logger::Log(DEBUG, __VA_ARGS__)
#define KE_LOG_CRITICAL(...)     Logger::Log(CRITICAL, __VA_ARGS__)
#define KE_LOG_TRACE(...)        Logger::Log(TRACE, __VA_ARGS__)
#define KE_TAG_LOG_INFO(tag, ...)    Logger::C_LOG(tag, INFO, __VA_ARGS__)
#define KE_TAG_LOG_WARN(tag, ...)    Logger::C_LOG(tag, WARN, __VA_ARGS__)
#define KE_TAG_LOG_DEBUG(tag, ...)   Logger::C_LOG(tag, DEBUG, __VA_ARGS__)
#define KE_TAG_LOG_CRITICAL(tag, ...) Logger::C_LOG(tag, CRITICAL, __VA_ARGS__)
#define KE_TAG_LOG_TRACE(tag, ...)   Logger::C_LOG(tag, TRACE, __VA_ARGS__)

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

#else // Release builds
#define KE_LOG_INFO(...) ((void)0)
#define KE_LOG_WARN(...) ((void)0)
#define KE_LOG_DEBUG(...) ((void)0)
#define KE_LOG_CRITICAL(...) ((void)0)
#define KE_LOG_TRACE(...) ((void)0)
#define KE_TAG_LOG_INFO(...) ((void)0)
#define KE_TAG_LOG_WARN(...) ((void)0)
#define KE_TAG_LOG_DEBUG(...) ((void)0)
#define KE_TAG_LOG_CRITICAL(...) ((void)0)
#define KE_TAG_LOG_TRACE(...) ((void)0)

#define KE_ASSERT(condition, ...) ((void)0)
#define KE_CORE_ASSERT(condition, ...) ((void)0)
#define KE_TAG_ASSERT(tag, condition, ...) ((void)0)
#endif