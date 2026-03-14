#pragma once

#include <events/categories/categories.hh>

namespace brasio::events::categories
{
    template <typename SubEventType>
    class WindowCategoryEvent
        : public Event<WindowCategoryEvent<SubEventType>, SubEventType>
    {
    public:
        WindowCategoryEvent(enum EventType eventType);
    };
} // namespace brasio::events::categories

#include <events/categories/window.hxx>
