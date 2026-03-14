#pragma once

#include <events/categories/categories.hh>

namespace brasio::events::subevents
{
    class WindowCloseEvent
        : public categories::WindowCategoryEvent<WindowCloseEvent>
    {
    public:
        WindowCloseEvent();

        virtual std::string getTypeName() const override
        {
            return "WindowCloseEvent";
        }
    };
} // namespace brasio::events::subevents
