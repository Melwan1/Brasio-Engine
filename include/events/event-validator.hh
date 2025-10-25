#pragma once

#include <events/libevents.hh>

class EventValidator
{
public:
    static bool validateEventType(enum EventCategoryType categoryType,
                                  enum EventType eventType);
};
