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

#  DevLog Entry – OpenGL Abstraction Layer & Rendering Pipeline
**Date:** 2025-07-08  
**Module:** Graphics/Rendering System  
**Author:** mikazama
---
##  Summary
- Completed **OpenGL abstraction layer** implementation following **The Cherno's architectural patterns** for cross-platform graphics API support.
- Successfully abstracted core OpenGL objects: **Vertex Arrays**, **Vertex Buffers**, **Index Buffers**, and **Buffer Layout** system.
- Established foundation for **platform-agnostic rendering** with clean, type-safe buffer management.
- **RESOLVED**: ImGui rendering issues through proper buffer swapping order in main render loop.
---
##  Key Highlights
- Implemented **`VertexArray`** class with automatic VAO binding/unbinding and buffer attachment.
- Created **`VertexBuffer`** and **`IndexBuffer`** abstractions with RAII-style resource management.
- Developed **`BufferLayout`** system for declarative vertex attribute specification:
  - Supports common data types (Float, Int, Bool) with automatic stride calculation.
  - Seamless integration with shader attribute locations.
- Built **`InputManager`** singleton for centralized input polling across all engine systems.
- Successfully integrated **ImGui** into the rendering pipeline with custom OpenGL backend.
- **Fixed critical rendering pipeline order** - moved window buffer swap to end of render loop.
---
##  Buffer Layout System
- Declarative vertex attribute definition using `BufferElement` specifications.
- Automatic stride and offset calculation for interleaved vertex data.
- Type-safe attribute binding with compile-time validation.
- Example usage:
  ```cpp
  BufferLayout layout = {
      { ShaderDataType::Float3, "a_Position" },
      { ShaderDataType::Float4, "a_Color" },
      { ShaderDataType::Float2, "a_TexCoord" }
  };
  ```
---
##  Current Architecture
- **Platform Layer**: OpenGL context management and window integration.
- **Abstraction Layer**: API-agnostic buffer objects and layout system.
- **Input System**: Singleton-based key/mouse state polling accessible engine-wide.
- **UI Layer**: ImGui integration with custom rendering backend.
---
##  Critical Bug Fix - ImGui Rendering
**Problem**: ImGui UI elements were not appearing or rendering incorrectly after abstraction layer implementation.

**Root Cause**: Buffer swapping (`M_Window->OnUpdate()`) was occurring before ImGui rendering completed, causing UI to be lost during the swap.

**Solution**: Reorganized main render loop to ensure proper rendering order:
```cpp
// WORKING ORDER:
while (m_Running) {
    // 1. Clear buffers
    rc.ClearColor(0.1f, 0.0, 0.1, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 2. Render scene
    m_Shader->Bind();
    m_VertexArray->Bind();
    glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetSize(), GL_UNSIGNED_INT, nullptr);
    
    // 3. Update game logic
    for (Layer* layer : m_LayerStack) {
        layer->OnUpdate();
    }
    
    // 4. Render ImGui UI
    m_ImGuiLayer->Begin();
    for (Layer* layer : m_LayerStack) {
        layer->OnImGuiRender();
    }
    m_ImGuiLayer->End();
    
    // 5. Present frame (buffer swap) - MUST BE LAST
    M_Window->OnUpdate();
}
```

**Key Insight**: In double-buffered rendering, all rendering operations must complete before buffer swap. The window's `OnUpdate()` method handles `glfwSwapBuffers()`, which must be the final operation.
---
##  Next Steps
1. **Implement Renderer abstraction** with command queue system for batched draw calls.
2. **Create RenderCommand interface** to abstract OpenGL-specific drawing operations.
3. **Add Shader abstraction** with uniform management and program linking.
4. **Implement basic Material system** for texture and shader binding coordination.
5. **Create debug overlay** for real-time buffer and render state inspection.
6. **Add render state validation** to prevent similar timing issues in future.
---
##  Technical Debt
- InputManager singleton creates tight coupling - consider event-driven input system integration.
- Buffer abstractions need explicit OpenGL error checking and validation.
- Missing automated resource cleanup on context loss/recreation.
- **Need render loop documentation** to prevent buffer swap timing regressions.
---
##  Impact
- **Clean separation** between engine code and graphics API specifics.
- **Simplified vertex data management** with declarative buffer layouts.
- **Foundation for multi-API support** (Vulkan, DirectX) in future iterations.
- **Improved debugging capability** through abstracted resource tracking.
- **Stable UI rendering** with proper frame presentation timing.
---
##  Lessons Learned
- **OpenGL state management** requires careful attention to operation ordering, especially with buffer swaps.
- **Double-buffering timing** is critical - all rendering must complete before presentation.
- **Debugging graphics issues** often requires understanding the underlying API's frame lifecycle.
- **Abstraction layers** must respect the constraints of the underlying graphics API.
---
*"Abstraction is not about hiding complexity, but about organizing it into manageable, reusable patterns. And sometimes, the devil is in the timing."*


#  DevLog Entry – Academic Break & Camera System Priority
**Date:** 2025-07-12  
**Module:** Engine Development Status  
**Author:** mikazama
---
##  Summary
- **Academic commitments** will likely interrupt engine development for an extended period.
- **Prioritizing Camera System implementation** as final major feature before potential hiatus.
- Current rendering pipeline is **stable and functional** - good stopping point if needed.
- **Documentation efforts** to preserve current architecture knowledge for future resumption.
---
##  Current Status
- **OpenGL abstraction layer** is complete and battle-tested.
- **Buffer management system** is robust with proper RAII patterns.
- **ImGui integration** is stable with resolved rendering pipeline issues.
- **Input system** is functional for basic camera controls.
- **Foundation is solid** for camera implementation - all prerequisite systems are in place.
---
##  Priority: Camera System Implementation
**Target Goal**: Complete a functional camera system before academic break.

**Core Requirements**:
- **Perspective/Orthographic projection** matrix management
- **View matrix calculation** from camera position, target, and up vectors
- **Input-driven camera controls** (WASD movement, mouse look)
- **Camera abstraction class** with clean interface for renderer integration
- **Basic camera types**: FPS-style and orbit cameras

**Technical Approach**:
```cpp
class Camera {
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
    glm::vec3 m_Position, m_Front, m_Up, m_Right;
    float m_Yaw, m_Pitch, m_FOV;
    
    void UpdateCameraVectors();
    void UpdateViewMatrix();
};
```

**Integration Points**:
- Shader uniform management for view/projection matrices
- Input system connection for real-time camera controls
- Renderer abstraction for matrix passing
---
##  Academic Reality Check
**Situation**: University coursework demands will likely consume available development time for the foreseeable future.

**Impact on Engine Development**:
- **Reduced development velocity** - from daily commits to potentially weeks between sessions
- **Context switching overhead** - will need robust documentation to resume work effectively
- **Feature scope reduction** - focus on completing essential systems rather than expanding

**Contingency Planning**:
- **Comprehensive documentation** of current architecture decisions
- **Code comments** explaining complex rendering pipeline logic
- **Clear TODO markers** for future development priorities
- **Modular design** allows for easy re-entry at any system level
---
##  Documentation Priority
**Critical Knowledge to Preserve**:
- **Rendering loop timing** - especially buffer swap ordering (learned the hard way)
- **OpenGL abstraction patterns** - how buffer objects integrate with VAOs
- **ImGui integration details** - custom backend implementation notes
- **Input system architecture** - singleton pattern rationale and alternatives considered

**Action Items**:
- Document camera system design decisions even if implementation is incomplete
- Create architectural overview diagrams for visual reference
- Maintain commit message quality for future archeology
- Consider recording brief video explanations of complex systems
---
##  Lessons Learned
- **Academic-hobby balance** is challenging but manageable with proper prioritization
- **Incremental progress** is more sustainable than marathon coding sessions
- **Good documentation** is an investment in future productivity
- **Completing core systems** provides satisfaction and clear restart points
- **Engine development** is a marathon, not a sprint - breaks are normal and healthy

**Philosophy**: *"Better to build a solid foundation slowly than to rush toward an unstable tower. The camera system will be my capstone before this academic chapter."*
---
##  Future Resumption Strategy
**When Academic Load Decreases**:
1. **Review current documentation** and architecture decisions
2. **Test existing systems** to ensure no regressions
3. **Complete camera system** if not finished
4. **Proceed with original roadmap**: Renderer abstraction, Materials, Textures
5. **Consider academic learnings** for potential engine improvements (graphics courses, mathematics, etc.)

**Long-term Vision**: This engine will be a multi-year project. Academic breaks are features, not bugs - they provide perspective and prevent burnout.
---
##  Commitment
- **Complete camera system** within current development capacity
- **Document thoroughly** before extended break
- **Maintain git hygiene** for clean project archaeology
- **Return stronger** with fresh perspective and academic insights

*"The best time to plant a tree was 20 years ago. The second best time is now. The third best time is after you finish your studies with a deeper understanding of the mathematics behind the magic."*
---
##  Technical Debt Acknowledgment
- **Input system** still needs event-driven architecture consideration
- **Error handling** in OpenGL abstractions needs improvement
- **Resource cleanup** on context loss not yet implemented
- **Render state validation** still pending
- **These can wait** - camera system takes priority for completion satisfaction

**Note**: Academic work in computer graphics, linear algebra, or software engineering may actually inform better solutions to current technical debt items.
---
##  Impact
- **Sustainable development approach** prioritizes long-term project health
- **Clear milestone completion** provides psychological closure for break period
- **Knowledge preservation** ensures smooth development resumption
- **Realistic expectations** prevent guilt and maintain motivation
- **Camera system completion** will provide significant functionality boost for future work

*"Every great engine was built one commit at a time, across many seasons of life."*