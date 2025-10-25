#pragma once

#include <events/libevents.hh>

class MouseEventEmitter : public DefaultEventEmitter
{
public:
    virtual void fire(MouseClickEvent &event) override;
    virtual void fire(MouseMoveEvent &event) override;
    virtual void fire(MouseReleaseEvent &event) override;
    virtual void fire(MouseScrollEvent &event) override;
};
