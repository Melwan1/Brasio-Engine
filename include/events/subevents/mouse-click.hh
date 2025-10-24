#pragma once

#include <events/libevents.hh>

class MouseClickEvent : public MouseCategoryEvent<MouseClickEvent>
{
public:
    MouseClickEvent();
};
