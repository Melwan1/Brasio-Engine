#pragma once

#include <events/subevents/subevents.hh>

class EventEmitter
{
public:
    virtual void fire(ApplicationRenderEvent &) = 0;
    virtual void fire(ApplicationTickEvent &) = 0;
    virtual void fire(ApplicationUpdateEvent &) = 0;
    virtual void fire(KeyboardLongPressEvent &) = 0;
    virtual void fire(KeyboardPressEvent &) = 0;
    virtual void fire(KeyboardReleaseEvent &) = 0;
    virtual void fire(MouseClickEvent &) = 0;
    virtual void fire(MouseMoveEvent &) = 0;
    virtual void fire(MouseReleaseEvent &) = 0;
    virtual void fire(MouseScrollEvent &) = 0;
    virtual void fire(UnknownEvent &) = 0;
    virtual void fire(WindowCloseEvent &) = 0;
    virtual void fire(WindowFocusEvent &) = 0;
    virtual void fire(WindowLostFocusEvent &) = 0;
    virtual void fire(WindowMoveEvent &) = 0;
    virtual void fire(WindowResizeEvent &) = 0;
};
