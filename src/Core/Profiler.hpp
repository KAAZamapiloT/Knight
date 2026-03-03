#pragma once

#include "EngineApi.hpp" 
#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>
#include <mutex>
#include <map>

/**
 * @file Profiler.h
 * @brief A header-only instrumentation profiler for performance and memory tracking.
 * @details Provides tools to measure function execution time and track memory allocations.
 * Performance results are output in a JSON format compatible with chrome://tracing.
 * Memory tracking is achieved by overloading global new/delete operators.
 */

 // --- Data Structures ---

 /**
  * @struct ProfileResult
  * @brief Stores the results of a single profiling timer scope.
  */
struct ProfileResult
{
    std::string Name;      ///< The name of the profiled scope (e.g., function name).
    long long Start, End;  ///< The start and end timestamps in microseconds.
    uint32_t ThreadID;     ///< The ID of the thread where the profiling occurred.
};

/**
 * @struct InstrumentationSession
 * @brief Represents a single profiling session (e.g., "Startup", "Runtime").
 */
struct InstrumentationSession
{
    std::string Name;      ///< The name of the session.
};

/**
 * @struct MemoryStats
 * @brief Holds statistics about memory usage.
 */
struct MemoryStats
{
    uint32_t TotalAllocated = 0; ///< Total bytes allocated since the application started.
    uint32_t TotalFreed = 0;     ///< Total bytes freed since the application started.

    /**
     * @brief Calculates the current number of bytes allocated.
     * @return The current memory usage in bytes.
     */
    uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};


// --- The Instrumentor (Singleton) ---

/**
 * @class Instrumentor
 * @brief A singleton class that collects and writes profiling data.
 * @details This class is the central hub for the profiler. It manages writing performance
 * results to a JSON file and tracks memory allocation statistics. It is thread-safe.
 */
class KNIGHT_ENGINE_API Instrumentor
{
public:
    Instrumentor()
        : m_CurrentSession(nullptr), m_ProfileCount(0)
    {
    }

    /**
     * @brief Begins a new profiling session.
     * @param name The name of the session (e.g., "Startup").
     * @param filepath The path to the output JSON file.
     */
    void BeginSession(const std::string& name, const std::string& filepath = "results.json")
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_OutputStream.open(filepath);
        WriteHeader();
        m_CurrentSession = new InstrumentationSession{ name };
    }

    /**
     * @brief Ends the current profiling session and closes the output file.
     */
    void EndSession()
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        WriteFooter();
        m_OutputStream.close();
        delete m_CurrentSession;
        m_CurrentSession = nullptr;
        m_ProfileCount = 0;
    }

    /**
     * @brief Writes a single profile result to the JSON output file.
     * @param result The ProfileResult to write.
     */
    void WriteProfile(const ProfileResult& result)
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        if (m_ProfileCount++ > 0)
            m_OutputStream << ",";

        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        m_OutputStream << "{";
        m_OutputStream << "\"cat\":\"function\",";
        m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
        m_OutputStream << "\"name\":\"" << name << "\",";
        m_OutputStream << "\"ph\":\"X\",";
        m_OutputStream << "\"pid\":0,";
        m_OutputStream << "\"tid\":" << result.ThreadID << ",";
        m_OutputStream << "\"ts\":" << result.Start;
        m_OutputStream << "}";

        m_OutputStream.flush();
    }

    /**
     * @brief Retrieves the current memory usage statistics.
     * @return A MemoryStats struct with the latest data.
     */
    static MemoryStats GetMemoryStats() { return Get().m_MemStats; }

    /**
     * @brief Called by the overloaded operator new to record an allocation.
     * @param size The number of bytes allocated.
     */
    void OnAllocate(size_t size) { m_MemStats.TotalAllocated += size; }

    /**
     * @brief Called by the overloaded operator delete to record a deallocation.
     * @param size The number of bytes freed.
     */
    void OnFree(size_t size) { m_MemStats.TotalFreed += size; }

    /**
     * @brief Gets the singleton instance of the Instrumentor.
     * @return A reference to the Instrumentor.
     */
    static Instrumentor& Get()
    {
        static Instrumentor instance;
        return instance;
    }
private:
    InstrumentationSession* m_CurrentSession;
    std::ofstream m_OutputStream;
    int m_ProfileCount;
    std::mutex m_Mutex;
    MemoryStats m_MemStats;
private:
    /// @brief Writes the header of the JSON trace file.
    void WriteHeader()
    {
        m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
        m_OutputStream.flush();
    }

    /// @brief Writes the footer of the JSON trace file.
    void WriteFooter()
    {
        m_OutputStream << "]}";
        m_OutputStream.flush();
    }
};

// --- The RAII Timer ---

/**
 * @class InstrumentationTimer
 * @brief An RAII-based timer for performance profiling.
 * @details When created, it records the start time. When it goes out of scope,
 * its destructor automatically records the elapsed time and submits it to the Instrumentor.
 */
class KNIGHT_ENGINE_API InstrumentationTimer
{
public:
    /**
     * @brief Constructs a timer and records the start time.
     * @param name The name of the scope being profiled.
     */
    InstrumentationTimer(const char* name)
        : m_Name(name), m_Stopped(false)
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    /**
     * @brief Destructor that automatically stops the timer if it's still running.
     */
    ~InstrumentationTimer()
    {
        if (!m_Stopped)
            Stop();
    }

    /**
     * @brief Stops the timer, calculates the duration, and writes the profile result.
     */
    void Stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });

        m_Stopped = true;
    }

private:
    const char* m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    bool m_Stopped;
};

// --- Global Operator Overloads for Memory Tracking ---
#if defined(_DEBUG) // Or your equivalent debug flag

/**
 * @brief Overloaded global operator new to track memory allocations.
 * @param size The number of bytes to allocate.
 * @return A pointer to the allocated memory.
 */
inline void* operator new(size_t size)
{
    Instrumentor::Get().OnAllocate(size);
    return malloc(size);
}

/**
 * @brief Overloaded global operator delete to track memory deallocations.
 * @param memory A pointer to the memory to free.
 * @param size The size of the memory block (provided by the compiler).
 */
inline void operator delete(void* memory, size_t size)
{
    Instrumentor::Get().OnFree(size);
    free(memory);
}
#endif


// Profiling macros
#if defined(_DEBUG) // Or your equivalent debug flag
    // This macro automatically gets the function signature
#define KE_PROFILE_FUNCTION() InstrumentationTimer timer(__FUNCSIG__)
// Use this for any other scope you want to time
#define KE_PROFILE_SCOPE(name) InstrumentationTimer timer(name)
// Call these at the start and end of your application
#define KE_PROFILE_BEGIN_SESSION(name, filepath) Instrumentor::Get().BeginSession(name, filepath)
#define KE_PROFILE_END_SESSION() Instrumentor::Get().EndSession()
#else
    // In Release builds, all these macros compile to nothing, so there is zero performance cost.
#define KE_PROFILE_FUNCTION()
#define KE_PROFILE_SCOPE(name)
#define KE_PROFILE_BEGIN_SESSION(name, filepath)
#define KE_PROFILE_END_SESSION()
#endif
