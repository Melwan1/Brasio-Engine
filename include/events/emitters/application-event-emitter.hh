#pragma once

#include <events/emitters/default-event-emitter.hh>
#include <events/listeners/application-event-listener.hh>

class ApplicationEventEmitter : public DefaultEventEmitter
{
public:
    virtual void fire(ApplicationRenderEvent &event) override;
    virtual void fire(ApplicationTickEvent &event) override;
    virtual void fire(ApplicationUpdateEvent &event) override;

    void addListener(ApplicationEventListener &listener);

private:
    std::vector<std::reference_wrapper<ApplicationEventListener>> _listeners;
};
