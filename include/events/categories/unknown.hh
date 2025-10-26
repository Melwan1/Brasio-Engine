#pragma once

#include <events/categories/categories.hh>

template <typename SubEventType>
class UnknownCategoryEvent
    : public Event<UnknownCategoryEvent<SubEventType>, SubEventType>
{
public:
    UnknownCategoryEvent(enum EventType eventType);
};

#include <events/categories/unknown.hxx>
