#pragma once

#include <events/categories/categories.hh>

namespace brasio::events::subevents
{
    class WindowFocusEvent
        : public categories::WindowCategoryEvent<WindowFocusEvent>
    {
    public:
        WindowFocusEvent();

        virtual std::string getTypeName() const override
        {
            return "WindowFocusEvent";
        }
    };
} // namespace brasio::events::subevents
