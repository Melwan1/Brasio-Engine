#pragma once

#include <events/listeners/default-event-listener.hh>

class ApplicationEventListener : public DefaultEventListener
{
public:
    virtual void onEvent(ApplicationRenderEvent &) override;
    virtual void onEvent(ApplicationTickEvent &) override;
    virtual void onEvent(ApplicationUpdateEvent &) override;
};
