#pragma once

#include <events/listeners/default-event-listener.hh>

class WindowEventListener : public DefaultEventListener
{
public:
    virtual void onEvent(WindowCloseEvent &) override;
    virtual void onEvent(WindowFocusEvent &) override;
    virtual void onEvent(WindowLostFocusEvent &) override;
    virtual void onEvent(WindowMoveEvent &) override;
    virtual void onEvent(WindowResizeEvent &) override;
};
