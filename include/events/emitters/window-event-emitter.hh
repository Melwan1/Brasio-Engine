#pragma once

#include <events/emitters/default-event-emitter.hh>
#include <events/listeners/window-event-listener.hh>

class WindowEventEmitter : public DefaultEventEmitter
{
public:
    virtual void fire(WindowCloseEvent &event) override;
    virtual void fire(WindowFocusEvent &event) override;
    virtual void fire(WindowLostFocusEvent &event) override;
    virtual void fire(WindowMoveEvent &event) override;
    virtual void fire(WindowResizeEvent &event) override;

    void addListener(WindowEventListener &listener);

private:
    std::vector<std::reference_wrapper<WindowEventListener>> _listeners;
};
