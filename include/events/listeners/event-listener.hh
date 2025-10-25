#pragma once

#include <events/subevents/subevents.hh>

class EventListener
{
public:
    virtual void onEvent(ApplicationRenderEvent &) = 0;
    virtual void onEvent(ApplicationTickEvent &) = 0;
    virtual void onEvent(ApplicationUpdateEvent &) = 0;
    virtual void onEvent(KeyboardLongPressEvent &) = 0;
    virtual void onEvent(KeyboardPressEvent &) = 0;
    virtual void onEvent(KeyboardReleaseEvent &) = 0;
    virtual void onEvent(MouseClickEvent &) = 0;
    virtual void onEvent(MouseMoveEvent &) = 0;
    virtual void onEvent(MouseReleaseEvent &) = 0;
    virtual void onEvent(MouseScrollEvent &) = 0;
    virtual void onEvent(UnknownEvent &) = 0;
    virtual void onEvent(WindowCloseEvent &) = 0;
    virtual void onEvent(WindowFocusEvent &) = 0;
    virtual void onEvent(WindowLostFocusEvent &) = 0;
    virtual void onEvent(WindowMoveEvent &) = 0;
    virtual void onEvent(WindowResizeEvent &) = 0;
};
