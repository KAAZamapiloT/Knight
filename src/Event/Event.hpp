#pragma once

#include "Engine.hpp"
#include "EngineApi.hpp"

/**
 * @brief Represents all specific types of events.
 * Used to uniquely identify event classes in the event system.
 */
enum class EventType {
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

/**
 * @brief Bitmask-based categories for event filtering and dispatching.
 * Enables subsystems to subscribe to entire categories of events.
 */
enum class EventCategory {
    None = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput = BIT(1),
    EventCategoryKeyboard = BIT(2),
    EventCategoryMouse = BIT(3),
    EventCategoryMouseButton = BIT(4),
    EventCatregoryAI = BIT(5),
    EventCategoryPhysics = BIT(6)
};

/**
 * @brief Macro for defining the type-related functions for a specific event class.
 * Injects GetType(), GetStaticType(), and GetName() methods.
 */
#define EVENT_CLASS_TYPE(type) \
    static EventType GetStaticType() { return EventType::type; }\
    virtual EventType GetType() const override { return GetStaticType(); }\
    virtual const char* GetName() const override { return #type; }

 /**
  * @brief Macro for defining category flags in an event class.
  */
#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }

  /**
   * @class Event
   * @brief Abstract base class for all engine events.
   *
   * All custom events must derive from this class and implement the required methods.
   * Provides event metadata, dispatch control, and optional priority tagging.
   */
class KNIGHT_ENGINE_API Event {
public:
    /**
     * @brief Constructor.
     * @param name Human-readable name of the event, useful for debugging/logging.
     */
    Event(const std::string& name) : m_Name(name) {}

    /**
     * @brief Virtual destructor for polymorphic use.
     */
    virtual ~Event() = default;

    /**
     * @brief Retrieves the name of the event.
     * @return The event's name as a string.
     */
    virtual std::string GetName() = 0;

    /**
     * @brief User-defined logic to process the event.
     * Must be implemented by all derived event classes.
     */
    virtual void Handle() = 0;

    /**
     * @brief Marks the event as handled.
     * Prevents further propagation in the system.
     * @param handled True if handled, false otherwise.
     */
    virtual void SetHandled(bool handled) {
        b_IsHandled = handled;
    }

    /**
     * @brief Checks if the event has already been handled.
     * @return True if handled, false otherwise.
     */
    virtual bool IsHandled() const {
        return b_IsHandled;
    }

    /**
     * @brief Checks if the event is marked as high priority.
     * @return True if high priority, false otherwise.
     */
    virtual bool IsHighPriority() const {
        return b_IsHighPriority;
    }

    /**
     * @brief Sets the priority level of the event.
     * @param highPriority True to mark as high priority.
     */
    virtual void SetHighPriority(bool highPriority) {
        b_IsHighPriority = highPriority;
    }

    /**
     * @brief Returns the unique type of the event.
     * Must be overridden using the EVENT_CLASS_TYPE macro.
     * @return EventType enum value.
     */
    virtual EventType GetType() const = 0;

    /**
     * @brief Returns the bitfield representing the event's categories.
     * Used for filtering event listeners.
     * @return Bitfield of EventCategory.
     */
    virtual int GetCategoryFlags() const = 0;

    /**
     * @brief Checks if the event belongs to a specific category.
     * @param category Category to check against.
     * @return True if event is in the category.
     */
    virtual bool IsInCategory(EventCategory category) const {
        return GetCategoryFlags() & static_cast<int>(category);
    }

private:
    std::string m_Name;        ///< Name of the event.
    bool b_IsHandled = false;  ///< Indicates if the event was already handled.
    bool b_IsHighPriority = false; ///< Indicates if the event is prioritized.
};
