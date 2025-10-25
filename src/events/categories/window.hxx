#pragma once

#include <events/categories/window.hh>

template <typename SubEventType>
WindowCategoryEvent<SubEventType>::WindowCategoryEvent(
    enum EventType eventType)
    : Event<WindowCategoryEvent<SubEventType>, SubEventType>(
          EVENT_CATEGORY_WINDOW, eventType)
{}
