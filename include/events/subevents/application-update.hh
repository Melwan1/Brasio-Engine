#pragma once

#include <events/libevents.hh>

class ApplicationUpdateEvent
    : public ApplicationCategoryEvent<ApplicationUpdateEvent>
{
public:
    ApplicationUpdateEvent();
};
