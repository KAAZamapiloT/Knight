#pragma once

/**
 * @file KnightEngine.h
 * @brief Main header file for the KnightEngine.
 * @details This file should be included by any client application (like the sandbox)
 * to gain access to all the core engine functionality. It simplifies the include
 * process by bundling all essential headers.
 */

 // --- Core Engine Systems ---
#include "Core/Core.h"
#include "Core/Application.hpp"
#include "Core/Logger.hpp"
#include "Core/Time.hpp"

// --- Layers ---
#include "Layer/Layer.hpp"
#include "UI/ImguiLayer.hpp"

// --- Events ---
#include "Event/Event.hpp"
#include "Event/ApplicationEvents.hpp"
#include"Event/WindowEvent.hpp"
#include "Event/KeyEvent.hpp"
#include "Event/MouseEvent.hpp"

// --- Input ---
#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include "Input/CameraController.hpp"
#include "Platform/WINDOWS/WindowsInput.hpp" // Note: Platform-specific

// --- Graphics & Rendering ---
#include "Graphics/Renderer.hpp"
#include "Graphics/RenderCommand.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Shader.hpp" // Assuming shaderComp.h is represented by Shader.hpp
#include "Graphics/Texture.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/BufferLayout.hpp"
#include "Graphics/Renderer2D.hpp"

// --- Standard Library ---
#include <filesystem>
#include <string>
#include <memory>
#include"KnightEnginepch.h"

// --- OPEN GL SPECIFIC --
#include "OpenGl/OpenGLShaderComp.hpp"
