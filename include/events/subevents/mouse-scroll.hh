#pragma once

#include <events/categories/categories.hh>

namespace brasio::events::subevents
{
    class MouseScrollEvent
        : public categories::MouseCategoryEvent<MouseScrollEvent>
    {
    public:
        enum MouseScrollDirection
        {
            MOUSE_SCROLL_UP,
            MOUSE_SCROLL_DOWN,
        };

        MouseScrollEvent(enum MouseScrollDirection mouseScrollDirection);

        enum MouseScrollDirection getDirection() const;

        virtual std::string getTypeName() const override
        {
            return "MouseScrollEvent";
        }

    private:
        enum MouseScrollDirection _mouseScrollDirection;
    };
} // namespace brasio::events::subevents
