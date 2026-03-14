#pragma once

#include <events/categories/mouse.hh>

namespace brasio::events::categories {
template <typename SubEventType>
MouseCategoryEvent<SubEventType>::MouseCategoryEvent(
    enum EventType eventType)
    : Event<MouseCategoryEvent<SubEventType>, SubEventType>(
          EVENT_CATEGORY_MOUSE, eventType)
{}}
