#pragma once

#include <events/categories/categories.hh>

namespace brasio::events::categories
{
    template <typename SubEventType>
    class MouseCategoryEvent
        : public Event<MouseCategoryEvent<SubEventType>, SubEventType>
    {
    public:
        MouseCategoryEvent(enum EventType eventType);
    };
} // namespace brasio::events::categories

#include <events/categories/mouse.hxx>
