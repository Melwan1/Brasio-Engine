#pragma once

#include <events/libevents.hh>

class MouseMoveEvent : public MouseCategoryEvent<MouseMoveEvent>
{
public:
    MouseMoveEvent();
};
