#  Logger System Design - KnightEngine

##  Overview
The logging system is built using `spdlog` to provide high-performance, type-safe, and easily configurable logging. This system supports:
-  Variadic arguments
-  Format strings
-  Multiple log levels
-  Easy future extensions (file sinks, in-game log viewer, etc.)

---

##  Why I Used a Static Logger Class

-  No need to instantiate logger objects.
-  Globally accessible — avoids using singletons.
-  Easily hooks into macros (`KE_LOG_INFO`, etc.).
-  Supports compile-time filtering via macros.

---

##  Log Levels Used
```cpp
enum LogLevel {
    CRITICAL,
    INFO,
    WARN,
    DEBUG
};
