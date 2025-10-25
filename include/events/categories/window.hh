#pragma once

#include <events/libevents.hh>

template <typename SubEventType>
class WindowCategoryEvent
    : public Event<WindowCategoryEvent<SubEventType>, SubEventType>
{
public:
    WindowCategoryEvent(enum EventType eventType);
};

#include <events/categories/window.hxx>
