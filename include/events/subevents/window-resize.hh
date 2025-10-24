#pragma once

#include <events/libevents.hh>

class WindowResizeEvent : public WindowCategoryEvent<WindowResizeEvent>
{
public:
    WindowResizeEvent();
};
