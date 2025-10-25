#pragma once

#include <events/libevents.hh>

class MouseClickEvent : public MouseCategoryEvent<MouseClickEvent>
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

private:
    enum MouseClickType _mouseClickType;
};
