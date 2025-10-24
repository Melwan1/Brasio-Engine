#pragma once

#include <events/libevents.hh>

template <typename SubEventType>
class MouseCategoryEvent
    : public Event<MouseCategoryEvent<SubEventType>, SubEventType>
{
public:
    MouseCategoryEvent(enum EventType eventType);
};

#include <events/categories/mouse.hxx>
