# =======================================================================
# CMake Configuration for KnightEngine
# This file now ONLY builds the engine as a static library.
# Place this file in the root directory of your project.
# =======================================================================

# 1. Basic Project Setup
# -----------------------------------------------------------------------
cmake_minimum_required(VERSION 3.16)
project(KnightEngineSolution VERSION 1.0 LANGUAGES CXX C)

# Set the C++ standard for the entire project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set a default build type if none is specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# =======================================================================
# 2. Build the KnightEngine Static Library
# =======================================================================

# --- Automatically find all engine source files ---
file(GLOB_RECURSE ENGINE_SOURCES
    "src/*.cpp"
    "src/*.c"
    "external/imgui-1.91.9b/*.cpp"
    "external/imgui-1.91.9b/backends/*.cpp"
    "external/stb_image/*.cpp"
    "external/src/glad.c"
    "shaders/*.cpp"
)

# --- Define the Static Library Target ---
add_library(KnightEngine STATIC ${ENGINE_SOURCES})

# --- Set Include Directories for the Engine ---
# PUBLIC: These paths are used by KnightEngine AND any project that links to it.
target_include_directories(KnightEngine PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/spdlog-1.15.3/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/glm-1.0.1"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/imgui-1.91.9b"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/imgui-1.91.9b/backends"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL3-3.2.14/include"
)
# PRIVATE: These paths are only needed to compile the engine itself.
target_include_directories(KnightEngine PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/external/stb_image"
)

# --- Link System Dependencies for the Engine (Windows) ---
if(WIN32)
    target_link_libraries(KnightEngine PUBLIC opengl32.lib)
endif()

# --- MSVC-Specific Compiler Flags for the Engine ---
if(MSVC)
    target_compile_options(KnightEngine PRIVATE
        /W3 # Set warning level to 3
        /source-charset:utf-8
        /execution-charset:utf-8
    )
    # Use the static runtime library to avoid DLL dependencies
    target_compile_options(KnightEngine PRIVATE "/MT$<$<CONFIG:Debug>:d>")
endif()

# =======================================================================
# 3. Output and IDE Organization
# =======================================================================

# --- Set Output Directories ---
# This organizes the final .lib file into a clean lib folder.
set_property(TARGET KnightEngine PROPERTY ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}")

# --- Create Source Groups for Visual Studio ---
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_SOURCES})

# --- Final Message ---
message(STATUS "CMake configuration complete. Build the 'KnightEngine' target to create the static library.")
