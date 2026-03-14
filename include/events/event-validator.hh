#pragma once

#include <events/libevents.hh>

namespace brasio::events
{
    class EventValidator
    {
    public:
        static bool validateEventType(enum EventCategoryType categoryType,
                                      enum EventType eventType);
    };
} // namespace brasio::events
