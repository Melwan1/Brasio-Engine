#pragma once

#include <events/categories/categories.hh>

namespace brasio::events::subevents
{
    class MouseClickEvent
        : public categories::MouseCategoryEvent<MouseClickEvent>
    {
    public:
        enum MouseClickType
        {
            MOUSE_CLICK_LEFT,
            MOUSE_CLICK_MIDDLE,
            MOUSE_CLICK_RIGHT,
        };

        MouseClickEvent(enum MouseClickType mouseClickType);

        enum MouseClickType getClickType() const;

        virtual std::string getTypeName() const override
        {
            return "MouseClickEvent";
        }

    private:
        enum MouseClickType _mouseClickType;
    };
} // namespace brasio::events::subevents
