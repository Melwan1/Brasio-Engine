#pragma once

#include <events/libevents.hh>

template <typename SubEventType>
class ApplicationCategoryEvent
    : public Event<ApplicationCategoryEvent<SubEventType>, SubEventType>
{
public:
    ApplicationCategoryEvent(enum EventType eventType);
};

#include <events/categories/application.hxx>
