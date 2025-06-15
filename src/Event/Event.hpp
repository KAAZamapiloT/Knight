#pragma once
#include<string>
#include "EngineApi.hpp"
#include"Engine.hpp"
namespace KnightEngine
{
	enum class Type {
		None = 0,
		WindowResize, WindowClose, WindowFocus, WindowLostFocus, WindowMoved, WindowMinimized,
		ApplicationTick, ApplicationUpdate, ApplicationRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	enum class Category
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	class KNIGHT_ENGINE_API Event
	{
	public:
		Event() = default;
		virtual ~Event() = default;
		// Event type enum
		virtual Type GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
		bool handled = false;
	};
}

