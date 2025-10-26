#pragma once

#include <events/listeners/default-event-listener.hh>

class MouseEventListener : public DefaultEventListener
{
public:
    virtual void onEvent(MouseClickEvent &) override;
    virtual void onEvent(MouseMoveEvent &) override;
    virtual void onEvent(MouseReleaseEvent &) override;
    virtual void onEvent(MouseScrollEvent &) override;
};
