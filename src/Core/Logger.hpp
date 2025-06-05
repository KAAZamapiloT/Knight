#pragma once
#include"spdlog/logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include<string>
#include <utility> 
#define KE_LOG_INFO(...)    Logger::Log(INFO, __VA_ARGS__)
#define KE_LOG_WARN(...)    Logger::Log(WARN, __VA_ARGS__)
#define KE_LOG_DEBUG(...)   Logger::Log(DEBUG, __VA_ARGS__)
#define KE_LOG_CRITICAL(...) Logger::Log(CRITICAL, __VA_ARGS__)
enum LogLevel
{
	CRITICAL,
	INFO,
	WARN,
	DEBUG
  

};
class Logger {
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
};

