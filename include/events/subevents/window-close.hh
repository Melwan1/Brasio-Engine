#pragma once

#include <events/libevents.hh>

class WindowCloseEvent : public WindowCategoryEvent<WindowCloseEvent>
{
public:
    WindowCloseEvent();
};
