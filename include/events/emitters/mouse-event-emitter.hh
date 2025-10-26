#pragma once

#include <events/emitters/default-event-emitter.hh>
#include <events/listeners/mouse-event-listener.hh>

class MouseEventEmitter : public DefaultEventEmitter
{
public:
    virtual void fire(MouseClickEvent &event) override;
    virtual void fire(MouseMoveEvent &event) override;
    virtual void fire(MouseReleaseEvent &event) override;
    virtual void fire(MouseScrollEvent &event) override;

    void addListener(MouseEventListener &listener);

private:
    std::vector<std::reference_wrapper<MouseEventListener>> _listeners;
};
