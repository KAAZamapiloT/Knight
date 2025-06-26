#pragma once
#include"spdlog/logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include<string>
#include <utility> 
#include "EngineApi.hpp"

/**
 * @enum LogLevel
 * @brief Defines different levels of logging severity.
 */
enum LogLevel
{
	CRITICAL, ///< Critical errors that cause the application to crash or become unusable.
	INFO,     ///< Informational messages that provide general information about the application's state.
	WARN,     ///< Warnings that indicate potential issues but do not stop the application from running.
	DEBUG
  

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

    }
};

//  Logging macros: disabled in Release, enabled in Debug
#if defined(_DEBUG) || !defined(NDEBUG)
#define KE_LOG_INFO(...)     Logger::Log(INFO, __VA_ARGS__)
#define KE_LOG_WARN(...)     Logger::Log(WARN, __VA_ARGS__)
#define KE_LOG_DEBUG(...)    Logger::Log(DEBUG, __VA_ARGS__)
#define KE_LOG_CRITICAL(...) Logger::Log(CRITICAL, __VA_ARGS__)

#define KE_TAG_LOG_INFO(tag, ...)    Logger::C_LOG(tag, INFO, __VA_ARGS__)
#define KE_TAG_LOG_WARN(tag, ...)    Logger::C_LOG(tag, WARN, __VA_ARGS__)
#define KE_TAG_LOG_DEBUG(tag, ...)   Logger::C_LOG(tag, DEBUG, __VA_ARGS__)
#define KE_TAG_LOG_CRITICAL(tag, ...) Logger::C_LOG(tag, CRITICAL, __VA_ARGS__)
#else
    // No-ops in ship build
#define KE_LOG_INFO(...)     Logger::NLog(INFO, __VA_ARGS__)
#define KE_LOG_WARN(...)     Logger::NLog(WARN, __VA_ARGS__)
#define KE_LOG_DEBUG(...)    Logger::NLog(DEBUG, __VA_ARGS__)
#define KE_LOG_CRITICAL(...) Logger::NLog(CRITICAL, __VA_ARGS__)

#define KE_TAG_LOG_INFO(tag, ...)    Logger::NC_LOG(tag, INFO, __VA_ARGS__)
#define KE_TAG_LOG_WARN(tag, ...)    Logger::NC_LOG(tag, WARN, __VA_ARGS__)
#define KE_TAG_LOG_DEBUG(tag, ...)   Logger::NC_LOG(tag, DEBUG, __VA_ARGS__)
#define KE_TAG_LOG_CRITICAL(tag, ...) Logger::NC_LOG(tag, CRITICAL, __VA_ARGS__)
#endif
/**
 * @def KE_LOG_INFO
 * @brief Logs an informational message in debug mode.
 * @details Expands to Logger::Log(INFO, ...) in debug builds.
 * In release builds, this is disabled to avoid runtime cost.
 *
 * @def KE_LOG_WARN
 * @brief Logs a warning message in debug mode.
 * @details Helpful for non-critical issues that might need investigation.
 *
 * @def KE_LOG_DEBUG
 * @brief Logs a debug message in debug mode.
 * @details Used for verbose logging and internal state dumps.
 *
 * @def KE_LOG_CRITICAL
 * @brief Logs a critical error message in debug mode.
 * @details Should be used for unrecoverable conditions or assertions.
 *
 * @def KE_TAG_LOG_INFO(tag, ...)
 * @brief Logs an informational message with a custom tag.
 * @details Prepends the tag to the message for easier filtering.
 *
 * @def KE_TAG_LOG_WARN(tag, ...)
 * @brief Logs a warning message with a custom tag.
 *
 * @def KE_TAG_LOG_DEBUG(tag, ...)
 * @brief Logs a debug message with a custom tag.
 *
 * @def KE_TAG_LOG_CRITICAL(tag, ...)
 * @brief Logs a critical message with a custom tag.
 *
 * @note All macros become no-ops in release builds to optimize performance.
 * You can control this behavior by defining or undefining _DEBUG or NDEBUG.
 *
 * @example
 * KE_LOG_INFO("Initialized subsystem X with value {}", value);
 * KE_TAG_LOG_WARN("Renderer", "Missing shader uniform: {}", name);
 */


#define KE_ASSERT(x, ...) { if(!(x)) { KE_LOG_CRITICAL("Assertion failed: {0}", __VA_ARGS__); std::abort(); } }
#define KE_CORE_ASSERT(x, ...) { if(!(x)) { KE_LOG_CRITICAL("Core assertion failed: {0}", __VA_ARGS__); std::abort(); } }
#define KE_CORE_ASSERT_TAG(tag, x, ...) { if(!(x)) { KE_TAG_LOG_CRITICAL(tag, "Core assertion failed: {0}", __VA_ARGS__); std::abort(); } }
