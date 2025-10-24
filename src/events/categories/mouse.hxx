#pragma once

#include <events/categories/mouse.hh>

template <typename SubEventType>
MouseCategoryEvent<SubEventType>::MouseCategoryEvent(
    enum EventType eventType)
    : Event<MouseCategoryEvent<SubEventType>, SubEventType>(
          EVENT_CATEGORY_MOUSE, eventType)
{}
