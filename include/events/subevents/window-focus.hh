#pragma once

#include <events/libevents.hh>

class WindowFocusEvent : public WindowCategoryEvent<WindowFocusEvent>
{
public:
    WindowFocusEvent();
};
