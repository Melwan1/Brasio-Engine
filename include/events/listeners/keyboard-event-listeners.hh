#pragma once

#include <events/listeners/default-event-listener.hh>

class KeyboardEventListener : public DefaultEventListener
{
public:
    virtual void onEvent(KeyboardLongPressEvent &) override;
    virtual void onEvent(KeyboardPressEvent &) override;
    virtual void onEvent(KeyboardReleaseEvent &) override;
};
