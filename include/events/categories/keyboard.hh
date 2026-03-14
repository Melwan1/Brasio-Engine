#pragma once

#include <events/event.hh>

namespace brasio::events::categories
{

    template <typename SubEventType>
    class KeyboardCategoryEvent
        : public Event<KeyboardCategoryEvent<SubEventType>, SubEventType>
    {
    public:
        KeyboardCategoryEvent(enum EventType eventType);
    };
} // namespace brasio::events::categories

#include <events/categories/keyboard.hxx>
