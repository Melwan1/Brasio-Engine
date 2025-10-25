#pragma once

#include <events/listeners/event-listener.hh>

class DefaultEventListener : public EventListener
{
public:
    virtual void onEvent(ApplicationRenderEvent &) override;
    virtual void onEvent(ApplicationTickEvent &) override;
    virtual void onEvent(ApplicationUpdateEvent &) override;
    virtual void onEvent(KeyboardLongPressEvent &) override;
    virtual void onEvent(KeyboardPressEvent &) override;
    virtual void onEvent(KeyboardReleaseEvent &) override;
    virtual void onEvent(MouseClickEvent &) override;
    virtual void onEvent(MouseMoveEvent &) override;
    virtual void onEvent(MouseReleaseEvent &) override;
    virtual void onEvent(MouseScrollEvent &) override;
    virtual void onEvent(UnknownEvent &) override;
    virtual void onEvent(WindowCloseEvent &) override;
    virtual void onEvent(WindowFocusEvent &) override;
    virtual void onEvent(WindowLostFocusEvent &) override;
    virtual void onEvent(WindowMoveEvent &) override;
    virtual void onEvent(WindowResizeEvent &) override;
};
