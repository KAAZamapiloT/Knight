cmake_minimum_required(VERSION 3.10)

project(Knight)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Vulkan
find_package(Vulkan REQUIRED)

# Set GLM directory (assuming it's inside the project folder)
set(GLM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/glm")

# Set source files (modify according to your project structure)
set(SOURCES
        main.cpp
)

# Add executable
#add_executable(Knight ${SOURCES})
add_executable(Knight main.cpp
        external/Vulkan-Headers/include/vulkan/vulkan.h
        external/GLFW/src/cocoa_joystick.h)
# Include directories (target-specific)
target_include_directories(Knight PRIVATE
        ${Vulkan_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/helpers/VSG
        ${CMAKE_SOURCE_DIR}/external/GLFW/include
        ${CMAKE_SOURCE_DIR}/external/Vulkan-Headers/include/vulkan
        ${CMAKE_SOURCE_DIR}/external/Vulkan-Headers/include/vk_video
)


# Link Vulkan
target_link_libraries(Knight Vulkan::Vulkan)
