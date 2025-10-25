#pragma once

#include <events/libevents.hh>

class KeyboardEventEmitter : public DefaultEventEmitter
{
public:
    virtual void fire(KeyboardPressEvent &event) override;
    virtual void fire(KeyboardLongPressEvent &event) override;
    virtual void fire(KeyboardReleaseEvent &event) override;
};
