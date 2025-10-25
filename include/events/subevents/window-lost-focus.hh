#pragma once

#include <events/libevents.hh>

class WindowLostFocusEvent : public WindowCategoryEvent<WindowLostFocusEvent>
{
public:
    WindowLostFocusEvent();
};
