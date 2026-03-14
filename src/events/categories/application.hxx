#pragma once

#include <events/categories/application.hh>

namespace brasio::events::categories {
template <typename SubEventType>
ApplicationCategoryEvent<SubEventType>::ApplicationCategoryEvent(
    enum EventType eventType)
    : Event<ApplicationCategoryEvent<SubEventType>, SubEventType>(
          EVENT_CATEGORY_APPLICATION, eventType)
{}}
