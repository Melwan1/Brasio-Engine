#pragma once

#include <events/categories/keyboard.hh>

template <typename SubEventType>
KeyboardCategoryEvent<SubEventType>::KeyboardCategoryEvent(
    enum EventType eventType)
    : Event<KeyboardCategoryEvent<SubEventType>, SubEventType>(
          EVENT_CATEGORY_KEYBOARD, eventType)
{}
