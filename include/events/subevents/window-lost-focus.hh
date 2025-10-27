#pragma once

#include <events/categories/categories.hh>

class WindowLostFocusEvent : public WindowCategoryEvent<WindowLostFocusEvent>
{
public:
    WindowLostFocusEvent();

    virtual std::string getTypeName() const override
    {
        return "WindowLostFocus";
    }
};
