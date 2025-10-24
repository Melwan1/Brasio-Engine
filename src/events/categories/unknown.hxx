#pragma once

#include <events/categories/unknown.hh>

template <typename SubEventType>
UnknownCategoryEvent<SubEventType>::UnknownCategoryEvent(
    enum EventType eventType)
    : Event<UnknownCategoryEvent<SubEventType>, SubEventType>(
          EVENT_CATEGORY_UNKNOWN, eventType)
{}
