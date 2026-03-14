#pragma once

#include <events/categories/categories.hh>

namespace brasio::events::categories
{
    template <typename SubEventType>
    class UnknownCategoryEvent
        : public Event<UnknownCategoryEvent<SubEventType>, SubEventType>
    {
    public:
        UnknownCategoryEvent(enum EventType eventType);
    };
} // namespace brasio::events::categories

#include <events/categories/unknown.hxx>
