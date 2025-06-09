#pragma once
#include<string>
#include "EngineApi.hpp"
class KNIGHT_ENGINE_API Event
{
public:
	Event() = default;
	virtual ~Event() = default;
	// Event type enum
	enum class Type {
		None = 0,
		WindowResize,
		KeyPressed,
		KeyReleased,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};
	virtual Type GetType() const = 0;
	virtual const char* GetName() const = 0;
	virtual std::string ToString() const { return GetName(); }
};

