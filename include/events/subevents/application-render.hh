#pragma once

#include <events/libevents.hh>

class ApplicationRenderEvent
    : public ApplicationCategoryEvent<ApplicationRenderEvent>
{
public:
    ApplicationRenderEvent();
};
