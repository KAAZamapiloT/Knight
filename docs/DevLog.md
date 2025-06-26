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

# DevLog Entry – Rendering System Abstractions & Progress

**Date:** 2025-06-14  
**Module:** Core Rendering System  
**Author:** mikazama

---

##  Progress Summary

- Abstracted and implemented core graphics API interfaces:
  - `VertexBuffer` and its implementation: `OpenGLVertexBuffer`
  - `IndexBuffer` and its implementation: `OpenGLIndexBuffer`
  - `VertexArray` and its implementation: `OpenGLVertexArray`
- Designed the system to support multiple rendering backends in the future via polymorphic interfaces.
- Ensured buffer creation and binding follow modern OpenGL practices.
- Basic vertex array management now handled in a modular, backend-agnostic way.
- Continued incremental setup for DLL-style modular engine compilation.

---

##  Next Steps

1. Complete implementation of `Mesh`, `Camera`, and `RenderCommand` classes.
2. Integrate `VertexArray` usage with `RenderCommand` to validate abstraction layer.
3. Set up rendering pipeline to draw a basic cube using abstracted buffer systems.
4. Finalize early-stage rendering loop.
5. Modularize the window layer if necessary, possibly with namespace wrapping.

---

##  Notes

- Abstracting buffers and VAOs was a key step toward achieving engine modularity.
- These abstractions form the spine of a cross-platform rendering API.
- With these systems in place, rendering logic can now decouple from OpenGL specifics.
- Important to maintain consistent ownership via `std::shared_ptr` across interfaces.


#  DevLog Entry – Event System Design & Research

**Date:** 2025-06-25  
**Module:** Core Event System  
**Author:** mikazama

---

##  Summary

- Spent focused time studying **The Cherno’s Hazel engine architecture** to understand best practices in event system design.
- Began **rebuilding and refactoring** the event system to align with modern, layered engine architecture.
- Key focus areas: event dispatching, propagation through layers, and structured handler definitions.

---

##  Key Highlights

- Implemented a basic **`EventDispatcher`** for type-safe event handling using templated dispatch.
- Integrated `Event` base class with virtual category/type checks.
- Verified the system's ability to:
  - Send window events (`WindowResizeEvent`, `WindowCloseEvent`) from the platform layer.
  - Route events via `Application::OnEvent()` to all layers in reverse order (top to bottom).
- Confirmed that **event `Handled` flags** work correctly to stop further propagation when needed.

---
##  Integration Approach

- Wiring `Window` class (GLFW/SDL abstraction) to generate events like `WindowResizeEvent` on actual OS events.
- Events are dispatched through `Application`, then to all active layers via `LayerStack`.
- Each layer defines `OnEvent(Event&)` for filtering and reacting to specific event types.

---

##  Next Steps

1. Refactor current window event subclasses to carry actual data and meaningful `Handle()` logic.
2. Create more **engine-specific events** (e.g., `AppTickEvent`, `SceneLoadEvent`, `AssetReloadEvent`).
3. Add editor-only event overlays/logging to trace event routing visually.
4. Explore optional **compile-time event type registration** or reflection-based routing for scripting support.

---

##  Notes

- Cherno’s explanation provided a **clean mental model** for event routing from OS → Engine Core → Game Layer.
- Strong focus on **type safety**, **flexibility**, and **minimal overhead**.
- Long-term goal: make the event system pluggable with script-based callbacks (e.g., Lua, Python).

---

##  Impact

- Improves **decoupling** between systems (e.g., input, window, renderer, UI).
- Makes the engine more maintainable and testable by tracing clear signal flow.
- Foundation for future **in-editor hot reloading** and **runtime debugging tools**.

---

_“Every event is a signal; the clearer the path it travels, the smarter the engine becomes.”_
