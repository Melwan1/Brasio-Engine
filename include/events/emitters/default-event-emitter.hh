#pragma once

#include <events/emitters/emitters.hh>

class DefaultEventEmitter : public EventEmitter
{
public:
    virtual void fire(ApplicationRenderEvent &) override;
    virtual void fire(ApplicationTickEvent &) override;
    virtual void fire(ApplicationUpdateEvent &) override;
    virtual void fire(KeyboardLongPressEvent &) override;
    virtual void fire(KeyboardPressEvent &) override;
    virtual void fire(KeyboardReleaseEvent &) override;
    virtual void fire(MouseClickEvent &) override;
    virtual void fire(MouseMoveEvent &) override;
    virtual void fire(MouseReleaseEvent &) override;
    virtual void fire(MouseScrollEvent &) override;
    virtual void fire(UnknownEvent &) override;
    virtual void fire(WindowCloseEvent &) override;
    virtual void fire(WindowFocusEvent &) override;
    virtual void fire(WindowLostFocusEvent &) override;
    virtual void fire(WindowMoveEvent &) override;
    virtual void fire(WindowResizeEvent &) override;
};
