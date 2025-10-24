#pragma once

#include <events/libevents.hh>

template <typename SubEventType>
class UnknownCategoryEvent
    : public Event<UnknownCategoryEvent<SubEventType>, SubEventType>
{
public:
    UnknownCategoryEvent(enum EventType eventType);
};

#include <events/categories/unknown.hxx>
