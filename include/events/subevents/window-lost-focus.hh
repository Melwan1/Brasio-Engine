#pragma once

#include <events/categories/categories.hh>

namespace brasio::events::subevents
{
    class WindowLostFocusEvent
        : public categories::WindowCategoryEvent<WindowLostFocusEvent>
    {
    public:
        WindowLostFocusEvent();

        virtual std::string getTypeName() const override
        {
            return "WindowLostFocus";
        }
    };
} // namespace brasio::events::subevents
