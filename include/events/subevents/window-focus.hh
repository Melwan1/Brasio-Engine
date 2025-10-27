#pragma once

#include <events/categories/categories.hh>

class WindowFocusEvent : public WindowCategoryEvent<WindowFocusEvent>
{
public:
    WindowFocusEvent();

    virtual std::string getTypeName() const override
    {
        return "WindowFocusEvent";
    }
};
