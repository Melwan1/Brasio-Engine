#pragma once

#include <events/emitters/emitters.hh>

class ApplicationEventEmitter : public DefaultEventEmitter
{
public:
    virtual void fire(ApplicationRenderEvent &event) override;
    virtual void fire(ApplicationTickEvent &event) override;
    virtual void fire(ApplicationUpdateEvent &event) override;
};
