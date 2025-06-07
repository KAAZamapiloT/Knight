#  DevLog Entry – Logging System Integration

** Date:** 2025-06-05  
** Module:** Core Logger System  
** Author:** mikazama

---

##  Summary
- Added `Logger` system using **spdlog**.
- Introduced standard logging macros:
  - `KE_LOG_INFO(...)`
  - `KE_LOG_WARN(...)`
  - `KE_LOG_DEBUG(...)`
  - `KE_LOG_CRITICAL(...)`

---

##  Features
- **Header-only logger** with static functions — no instantiation needed.
- **Tagged logging** (`C_LOG` planned) for subsystem-specific tracing (e.g., `"Animation"`, `"Physics"`, `"Audio"`).
- Logger supports **variadic arguments** using `std::forward` for high performance and formatting flexibility.
- Centralized log level handling using an `enum LogLevel`.

---

##  Next Steps
-  Integrate logging across **other systems** (`Renderer`, `Input`, `Scene`, `UI`, etc.)
-  Add **compile-time logging control**:
  - Disable or reduce logging in **Release mode** using `#ifdef DEBUG` or `#ifndef NDEBUG`.
  - Potential macro-based filtering for critical-only logs in performance-critical builds.
-  Optional: Add log file sink (e.g., `engine_log.txt`) for runtime debugging and crash reports.

---

##  Notes
- `spdlog` requires UTF-8; all sources must be compiled with `/utf-8`.
- `APIENTRY` redefinition warning resolved by checking `glad.h` inclusion order — should be handled centrally.

---

##  Impact
-  Engine systems can now trace execution paths without manual `std::cout` clutter.
-  Easier future integration with:
  - On-screen developer console (via ImGui)
  - Remote debug log streaming
  - Performance analysis tools

---

_“Logs are your eyes into a blind engine — see what it’s thinking.”_

# DevLog Entry – Work Started on Rendering System

**Date:** 2025-06-07  
**Module:** Core Rendering System  
**Author:** mikazama

---

## Progress Summary

- Started laying the groundwork for the rendering system.
- Added foundational classes: `Mesh.h`, `Camera.h`, `RenderCommand.h`.
- Planning to implement these classes next.
- Next major milestone: render a cube on screen to verify the rendering pipeline.
- Concurrently working on structuring the engine build system to support compilation as a DLL.

---

## Next Steps

1. Implement the core functionality of `Mesh`, `Camera`, and `RenderCommand`.
2. Set up the rendering pipeline to draw a basic cube.
3. Continue framework adjustments for DLL compilation support.

---

## Notes

This phase is critical to establishing a solid rendering foundation while preparing the engine for modular deployment.
