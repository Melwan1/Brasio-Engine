#pragma once

#include <events/categories/categories.hh>

template <typename SubEventType>
class MouseCategoryEvent
    : public Event<MouseCategoryEvent<SubEventType>, SubEventType>
{
public:
    MouseCategoryEvent(enum EventType eventType);
};

#include <events/categories/mouse.hxx>
