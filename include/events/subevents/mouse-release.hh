#pragma once

#include <events/libevents.hh>

class MouseReleaseEvent : public MouseCategoryEvent<MouseReleaseEvent>
{
public:
    MouseReleaseEvent();
};
