#pragma once

#include <events/libevents.hh>

template <typename SubEventType>
class KeyboardCategoryEvent
    : public Event<KeyboardCategoryEvent<SubEventType>, SubEventType>
{
public:
    KeyboardCategoryEvent(enum EventType eventType);
};

#include <events/categories/keyboard.hxx>
