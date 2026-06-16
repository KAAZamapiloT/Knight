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
| Event System      | ✅ Basic   | Input, resize, dispatch      |
| Scene Graph       | ❌ Planned | ECS or simple node hierarchy |
| Editor Tools      | ❌ Future  | Using ImGui                  |

---

## ✨ How to Use KnightEngine (Static `.lib` Version)

KnightEngine is structured as a **static library**, designed to be used as a reusable engine module. You build your game (e.g., `Sandbox`) as a separate project and link it to the engine.

---

### ✅ Step-by-Step Setup

#### 1. 📆 Clone KnightEngine

```bash
git clone https://github.com/yourusername/KnightEngine.git
```

---

#### 2. 📂 Set Up Folder Structure

Create a new Visual Studio **Solution** with the following structure:

```
/YourSolution
  /KnightEngine        <-- Cloned repo
    /src
    /external
  /Sandbox             <-- Your game or test project
```

---

#### 3. 🧱 Add Projects to Solution

* Open Visual Studio
* Create a new solution or open an existing one
* **Add Existing Project** → `KnightEngine/KnightEngine.vcxproj`
* **Create New Console Application** → Name it `Sandbox`
* **Set `Sandbox` as the Startup Project**

---

#### 4. 🔗 Configure Sandbox to Use KnightEngine

Right-click on `Sandbox` → **Properties**:

* **C/C++ → General → Additional Include Directories**:

  ```plaintext
  ../KnightEngine/src
  ../KnightEngine/external
  ```

* **Linker → General → Additional Library Directories**:

  ```plaintext
  ../KnightEngine/x64/$(Configuration)/
  ```

* **Linker → Input → Additional Dependencies**:

  ```plaintext
  KnightEngine.lib
  ```

* **Project Dependencies**:

  * Right-click the solution → **Project Dependencies**
  * Make sure `Sandbox` depends on `KnightEngine`

---

#### 5. 🛠️ Build and Run

* Build the solution (KnightEngine builds first, then Sandbox)
* In `Sandbox`, write your `main()` that uses the engine:

  ```cpp
 
  
   #include "Core/Application.hpp"
   int main()
  {
	KnightEngine::Application* app = new KnightEngine::Application();
	app->Run();
   }

  ```

---
---

### 🐟 Cross-Platform (Linux/macOS) – CMake Setup

If you're on **Linux** or **macOS**, you will need to:

#### 1. 📆 Clone KnightEngine

```bash
git clone https://github.com/yourusername/KnightEngine.git
```

#### 2. 🛠️ Create Your Project Structure

```
/MyGame
  /KnightEngine     <-- Cloned repo
  /Sandbox          <-- Your game project
  /CMakeLists.txt   <-- Your top-level CMake file
```

#### 3. ⚙️ Write CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyGame)

set(CMAKE_CXX_STANDARD 17)

# Add KnightEngine
add_subdirectory(KnightEngine)

# Add your own application
add_executable(Sandbox Sandbox/src/main.cpp)

# Include directories
target_include_directories(Sandbox PRIVATE
    KnightEngine/src
    KnightEngine/external
)

# Link the engine statically
target_link_libraries(Sandbox PRIVATE KnightEngine)
```

Then build with:

```bash
mkdir build
cd build
cmake ..
make
```

> ✅ Ensure the KnightEngine directory contains a valid `CMakeLists.txt` to build as a static library.

---
### ⚠️ Important Notes

* 🔧 **Both projects must match configurations**:

  * Runtime Library: `/MD` or `/MDd` (Release/Debug)
  * Platform Toolset and C++ Standard
* 🧠 You need to **include both the `.lib` file and the engine headers** to use the engine
* ❌ No need to ship `.dll` — the engine is statically linked into the final executable

---



