#pragma once

#include <events/categories/categories.hh>

class WindowFocusEvent : public WindowCategoryEvent<WindowFocusEvent>
{
public:
    WindowFocusEvent();
};
