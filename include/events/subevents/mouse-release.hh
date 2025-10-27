#pragma once

#include <events/categories/mouse.hh>

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

    virtual std::string getTypeName() const override
    {
        return "MouseReleaseEvent";
    }

private:
    enum MouseReleaseType _mouseReleaseType;
};
