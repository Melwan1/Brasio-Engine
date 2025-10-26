#pragma once

#include <events/categories/categories.hh>

class WindowCloseEvent : public WindowCategoryEvent<WindowCloseEvent>
{
public:
    WindowCloseEvent();
};
