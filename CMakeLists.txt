cmake_minimum_required(VERSION 3.20)

project(KnightEngine VERSION 1.0.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Platform-specific settings
if(WIN32)
    set(CMAKE_SYSTEM_VERSION 10.0)
    add_definitions(-DWIN32 -D_CONSOLE -DUNICODE -D_UNICODE)
endif()

# Build type specific definitions
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D_DEBUG)
else()
    add_definitions(-DNDEBUG)
endif()

# Enable UTF-8 support for MSVC
if(MSVC)
    add_compile_options(/source-charset:utf-8 /execution-charset:utf-8)
    # Set warning level
    add_compile_options(/W3)
    # Enable SDL checks
    add_compile_options(/sdl)
    # Enable conformance mode
    add_compile_options(/permissive-)

    # Release-specific optimizations
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(/GL)  # Whole program optimization
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG /OPT:REF /OPT:ICF")
    endif()
endif()

# Set external libraries base path
set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)

# You may need to adjust these paths based on your actual directory structure
# Check if these directories exist in your project:
# - external/spdlog-1.15.3/include
# - external/glm-1.0.1
# - external/SDL3-3.2.14/include
# - external/imgui-1.91.9b

# Include directories
set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    ${EXTERNAL_DIR}/spdlog-1.15.3/include
    ${EXTERNAL_DIR}/glm-1.0.1
    ${EXTERNAL_DIR}/SDL3-3.2.14/include
    ${EXTERNAL_DIR}/imgui-1.91.9b
    ${EXTERNAL_DIR}/imgui-1.91.9b/backends
    ${EXTERNAL_DIR}/include
)

# Library directories
if(WIN32)
    # TODO: Update this path to match your actual setup
    # Original path was: H:\GameEngine\KnightEngine\KnightEngine\external\SDL3-3.2.14\lib\x64
    # This assumes your project is in the current directory structure
    set(LIBRARY_DIRS
        ${EXTERNAL_DIR}/SDL3-3.2.14/lib/x64
    )
endif()

# Source files
set(SOURCES
    KnightEngine.cpp
    src/Core/Application.cpp
    src/Core/Logger.cpp
    src/Platform/Windows.cpp
    src/Platform/GLContext.cpp
    src/Graphics/Renderer.cpp
    src/Graphics/ForwardRenderer.cpp
    src/Graphics/Shader.cpp
    src/Graphics/Texture.cpp
    src/OpenGl/OpenGLGraphicsAPI.cpp
    src/UI/ImguiLayer.cpp
    src/input/InputManager.cpp
    external/src/glad.c
    external/imgui-1.91.9b/imgui.cpp
    external/imgui-1.91.9b/imgui_demo.cpp
    external/imgui-1.91.9b/imgui_draw.cpp
    external/imgui-1.91.9b/imgui_tables.cpp
    external/imgui-1.91.9b/imgui_widgets.cpp
    external/imgui-1.91.9b/backends/imgui_impl_opengl3.cpp
    external/imgui-1.91.9b/backends/imgui_impl_sdl3.cpp
)

# Header files (for IDE organization)
set(HEADERS
    src/Engine.hpp
    src/Core/Application.hpp
    src/Core/Logger.hpp
    src/Core/Time.hpp
    src/Platform/Windows.hpp
    src/Platform/GLContext.hpp
    src/Graphics/Renderer.hpp
    src/Graphics/ForwardRenderer.hpp
    src/Graphics/Shader.hpp
    src/Graphics/Texture.hpp
    src/Graphics/GraphicsApi.hpp
    src/OpenGl/OpenGLGraphicsAPI.h
    src/UI/ImguiLayer.hpp
    src/input/InputManager.h
    src/ECS/Component.hpp
    src/ECS/Entity.hpp
    src/ECS/Registory.h
    src/ECS/System.hpp
    src/utils/FileIO.hpp
    src/utils/Math.hpp
    shaders/triangle.h
    shaders/shapes.h
    external/include/glad/glad.h
    external/include/KHR/khrplatform.h
    external/imgui-1.91.9b/imgui.h
    external/imgui-1.91.9b/imconfig.h
    external/imgui-1.91.9b/backends/imgui_impl_opengl3.h
    external/imgui-1.91.9b/backends/imgui_impl_sdl3.h
)

# Documentation files
set(DOCS
    docs/DevLog.md
    docs/Logger.md
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${DOCS})

# Set target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

# Link directories
if(WIN32)
    target_link_directories(${PROJECT_NAME} PRIVATE ${LIBRARY_DIRS})
endif()

# Link libraries
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL3
        opengl32
    )
elseif(UNIX AND NOT APPLE)
    # Linux libraries
    find_package(PkgConfig REQUIRED)

    # Try to find SDL3 first, fallback to SDL2 if SDL3 isn't available
    pkg_check_modules(SDL3 sdl3)
    if(NOT SDL3_FOUND)
        message(WARNING "SDL3 not found, you may need to install it manually or use your bundled version")
        # Use your bundled SDL3 headers
        target_include_directories(${PROJECT_NAME} PRIVATE ${EXTERNAL_DIR}/SDL3-3.2.14/include)
        # You'll need to provide libSDL3.so in your external directory or install it system-wide
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL3)
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_LIBRARIES})
        target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_INCLUDE_DIRS})
        target_compile_options(${PROJECT_NAME} PRIVATE ${SDL3_CFLAGS_OTHER})
    endif()

    # Standard Linux libraries
    target_link_libraries(${PROJECT_NAME} PRIVATE
        GL
        dl
        pthread
        m  # math library
    )

    # Linux-specific compiler flags
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra
    )
elseif(APPLE)
    # macOS libraries
    find_library(SDL3_LIBRARY SDL3)
    find_package(OpenGL REQUIRED)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SDL3_LIBRARY}
        ${OPENGL_LIBRARIES}
    )
endif()

# Set output directories
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Copy SDL3 DLL to output directory on Windows
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${EXTERNAL_DIR}/SDL3-3.2.14/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMENT "Copying SDL3.dll to output directory"
    )
endif()

# Create source groups for better IDE organization
source_group("Source Files\\Core" FILES
    src/Core/Application.cpp
    src/Core/Logger.cpp
)

source_group("Source Files\\Platform" FILES
    src/Platform/Windows.cpp
    src/Platform/GLContext.cpp
)

source_group("Source Files\\Graphics" FILES
    src/Graphics/Renderer.cpp
    src/Graphics/ForwardRenderer.cpp
    src/Graphics/Shader.cpp
    src/Graphics/Texture.cpp
)

source_group("Source Files\\OpenGL" FILES
    src/OpenGl/OpenGLGraphicsAPI.cpp
)

source_group("Source Files\\UI" FILES
    src/UI/ImguiLayer.cpp
)

source_group("Source Files\\Input" FILES
    src/input/InputManager.cpp
)

source_group("Source Files\\External\\GLAD" FILES
    external/src/glad.c
)

source_group("Source Files\\External\\ImGui" FILES
    external/imgui-1.91.9b/imgui.cpp
    external/imgui-1.91.9b/imgui_demo.cpp
    external/imgui-1.91.9b/imgui_draw.cpp
    external/imgui-1.91.9b/imgui_tables.cpp
    external/imgui-1.91.9b/imgui_widgets.cpp
    external/imgui-1.91.9b/backends/imgui_impl_opengl3.cpp
    external/imgui-1.91.9b/backends/imgui_impl_sdl3.cpp
)

source_group("Header Files\\Core" FILES
    src/Core/Application.hpp
    src/Core/Logger.hpp
    src/Core/Time.hpp
)

source_group("Header Files\\Platform" FILES
    src/Platform/Windows.hpp
    src/Platform/GLContext.hpp
)

source_group("Header Files\\Graphics" FILES
    src/Graphics/Renderer.hpp
    src/Graphics/ForwardRenderer.hpp
    src/Graphics/Shader.hpp
    src/Graphics/Texture.hpp
    src/Graphics/GraphicsApi.hpp
)

source_group("Header Files\\ECS" FILES
    src/ECS/Component.hpp
    src/ECS/Entity.hpp
    src/ECS/Registory.h
    src/ECS/System.hpp
)

source_group("Documentation" FILES ${DOCS})

# Print configuration info
message(STATUS "KnightEngine Configuration:")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Platform: ${CMAKE_SYSTEM_NAME}")
if(WIN32)
    message(STATUS "  Target Platform Version: ${CMAKE_SYSTEM_VERSION}")
endif()
