#pragma once

#include <events/libevents.hh>

class MouseScrollEvent : public MouseCategoryEvent<MouseScrollEvent>
{
public:
    enum MouseScrollDirection
    {
        MOUSE_SCROLL_UP,
        MOUSE_SCROLL_DOWN,
    };

    MouseScrollEvent(enum MouseScrollDirection mouseScrollDirection);

    enum MouseScrollDirection getDirection() const;

private:
    enum MouseScrollDirection _mouseScrollDirection;
};
