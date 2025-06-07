#pragma once
#include"spdlog/logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include<string>
#include <utility> 
#include "EngineApi.hpp"
enum LogLevel
{
	CRITICAL,
	INFO,
	WARN,
	DEBUG
  

};
class KNIGHT_ENGINE_API Logger {
public:
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
    template<typename... Args>
    static void C_LOG(const std::string tag, LogLevel level, const char* fmt, Args&&... args) {
        std::string tagged_fmt = "[" + tag + "] " + fmt;
        Log(level, tagged_fmt.c_str(), std::forward<Args>(args)...);
    }
	template<typename... Args>
	static void NLog(LogLevel level, const char* format, Args&&... args) {
	
	}
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
