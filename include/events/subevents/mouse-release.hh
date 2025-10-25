#pragma once

#include <events/libevents.hh>

class MouseReleaseEvent : public MouseCategoryEvent<MouseReleaseEvent>
{
public:
    enum MouseReleaseType
    {
        MOUSE_RELEASE_LEFT,
        MOUSE_RELEASE_MIDDLE,
        MOUSE_RELEASE_RIGHT,
    };

    MouseReleaseEvent(enum MouseReleaseType mouseReleaseType);

    enum MouseReleaseType getReleaseType() const;

private:
    enum MouseReleaseType _mouseReleaseType;
};
