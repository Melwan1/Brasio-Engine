#pragma once

#include <events/libevents.hh>

class WindowMoveEvent : public WindowCategoryEvent<WindowMoveEvent>
{
public:
    WindowMoveEvent();
};
