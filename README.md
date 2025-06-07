# Knight Engine 🚀

> **Status:** ⚒️ In Development | 🎯 Goal: Learn Math, Graphics Programming, and Engine Architecture

Knight Engine is a **work-in-progress cross-platform C++ game engine**, designed with the primary goal of mastering the fundamentals of **graphics programming**, **math for real-time rendering**, and **low-level engine systems**.

It features modular design, a growing abstraction layer over rendering APIs, and is built from scratch without relying on large third-party engines.

---

## ✨ Core Objectives

- 🧠 **Learn 3D Math** – Transformations, vectors, matrices, projections
- 🎮 **Understand Graphics Pipelines** – OpenGL/Vulkan rendering layers
- 🧱 **Build Engine Architecture** – Modular, clean, layered design
- 🔧 **DLL/EXE Architecture** – Support for both engine DLL and executable applications

---

## 🚧 Current Progress

- ✅ Basic engine framework created
- ✅ Cross-platform macro system (`KNIGHT_ENGINE_API`)
- ✅ Core rendering abstraction defined
- ✅ `OpenGLGraphicsAPI`, `Texture`, `Mesh`, `Camera`, `RenderCommand` under development
- ✅ Logging system integrated
- 🛠️ DLL build system under setup
- 🧪 First rendering target: **draw a cube using custom rendering pipeline**

---

## 🔩 Tech Stack

- **Language:** C++
- **Rendering APIs:** OpenGL (initial), Vulkan (planned)
- **Libraries Used:**
  - [GLAD](https://github.com/Dav1dde/glad) – OpenGL Loader
  - [SDL3](https://github.com/libsdl-org/SDL) – Window & Input
  - [ImGui](https://github.com/ocornut/imgui) – GUI for tools
  - [GLM](https://github.com/g-truc/glm) – Math
- **Build System:** Visual Studio (Windows) / CMake (Planned)

---

## 🧠 Learning-Focused Design

Knight Engine is not trying to compete with Unreal or Unity — it’s designed as a learning ground. Expect raw, low-level systems, high modularity, and an emphasis on **understanding what's under the hood**.

Key areas:
- Manual memory layout for objects
- Logging, assertion, and diagnostics system
- Graphics pipeline setup from scratch
- Real-time math transformations
- Platform abstraction (Windows/macOS/Linux)

---

## 🗺️ Planned Features

| Subsystem         | Status     | Notes                        |
|------------------|------------|------------------------------|
| Renderer API      | 🛠️ WIP     | OpenGL backend in progress   |
| Texture System    | 🛠️ WIP     | Supports 2D textures         |
| Mesh & Model Load | ❌ Planned | Via custom or Assimp         |
| Math Module       | ✅ Basic   | GLM-based, extendable        |
| Event System      | ❌ Planned | Input, resize, dispatch      |
| Scene Graph       | ❌ Planned | ECS or simple node hierarchy |
| Editor Tools      | ❌ Future  | Using ImGui                  |

---

## 💡 How to Use (Planned)

```bash
git clone https://github.com/yourusername/KnightEngine.git
cd KnightEngine

