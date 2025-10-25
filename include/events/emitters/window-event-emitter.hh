#pragma once

#include <events/libevents.hh>

class WindowEventEmitter : public DefaultEventEmitter
{
public:
    virtual void fire(WindowCloseEvent &event) override;
    virtual void fire(WindowFocusEvent &event) override;
    virtual void fire(WindowLostFocusEvent &event) override;
    virtual void fire(WindowMoveEvent &event) override;
    virtual void fire(WindowResizeEvent &event) override;
};
