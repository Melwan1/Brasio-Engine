#pragma once

#include <events/categories/categories.hh>

template <typename SubEventType>
class WindowCategoryEvent
    : public Event<WindowCategoryEvent<SubEventType>, SubEventType>
{
public:
    WindowCategoryEvent(enum EventType eventType);
};

#include <events/categories/window.hxx>
