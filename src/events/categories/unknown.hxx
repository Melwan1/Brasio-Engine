#pragma once

#include <events/categories/unknown.hh>

namespace brasio::events::categories {
template <typename SubEventType>
UnknownCategoryEvent<SubEventType>::UnknownCategoryEvent(
    enum EventType eventType)
    : Event<UnknownCategoryEvent<SubEventType>, SubEventType>(
          EVENT_CATEGORY_UNKNOWN, eventType)
{}}
