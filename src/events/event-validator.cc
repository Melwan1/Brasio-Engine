#include <events/event-validator.hh>
#include "events/event-category-type.hh"
#include "events/event-type.hh"

namespace brasio::events
{
    bool EventValidator::validateEventType(enum EventCategoryType categoryType,
                                           enum EventType eventType)
    {
        switch (categoryType)
        {
        case EVENT_CATEGORY_WINDOW:
            return eventType == EVENT_WINDOW_CLOSE
                || eventType == EVENT_WINDOW_FOCUS
                || eventType == EVENT_WINDOW_LOST_FOCUS
                || eventType == EVENT_WINDOW_MOVE
                || eventType == EVENT_WINDOW_RESIZE;
        case EVENT_CATEGORY_APPLICATION:
            return eventType == EVENT_APPLICATION_TICK
                || eventType == EVENT_APPLICATION_RENDER
                || eventType == EVENT_APPLICATION_UPDATE;
        case EVENT_CATEGORY_KEYBOARD:
            return eventType == EVENT_KEYBOARD_PRESS
                || eventType == EVENT_KEYBOARD_LONG_PRESS
                || eventType == EVENT_KEYBOARD_RELEASE;
        case EVENT_CATEGORY_MOUSE:
            return eventType == EVENT_MOUSE_CLICK
                || eventType == EVENT_MOUSE_RELEASE
                || eventType == EVENT_MOUSE_MOVE
                || eventType == EVENT_MOUSE_SCROLL;
        case EVENT_CATEGORY_UNKNOWN:
            return eventType == EVENT_UNKNOWN;
        }
        return false;
    }
} // namespace brasio::events
