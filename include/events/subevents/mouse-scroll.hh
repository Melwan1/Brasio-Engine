#pragma once

#include <events/libevents.hh>

class MouseScrollEvent : public MouseCategoryEvent<MouseScrollEvent>
{
public:
    MouseScrollEvent();
};
