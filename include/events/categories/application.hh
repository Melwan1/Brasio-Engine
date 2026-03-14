#pragma once

#include <events/event.hh>

namespace brasio::events::categories
{
    template <typename SubEventType>
    class ApplicationCategoryEvent
        : public Event<ApplicationCategoryEvent<SubEventType>, SubEventType>
    {
    public:
        ApplicationCategoryEvent(enum EventType eventType);
    };
} // namespace brasio::events::categories

#include <events/categories/application.hxx>
