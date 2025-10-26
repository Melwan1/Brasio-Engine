#pragma once

#include <events/emitters/default-event-emitter.hh>
#include <events/listeners/keyboard-event-listeners.hh>

class KeyboardEventEmitter : public DefaultEventEmitter
{
public:
    virtual void fire(KeyboardPressEvent &event) override;
    virtual void fire(KeyboardLongPressEvent &event) override;
    virtual void fire(KeyboardReleaseEvent &event) override;

    void addListener(KeyboardEventListener &listener);

private:
    std::vector<std::reference_wrapper<KeyboardEventListener>> _listeners;
};
