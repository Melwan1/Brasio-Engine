#pragma once

#include <events/libevents.hh>

class ApplicationTickEvent
    : public ApplicationCategoryEvent<ApplicationTickEvent>
{
public:
    ApplicationTickEvent();
};
