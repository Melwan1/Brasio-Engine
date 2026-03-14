#pragma once

#include <events/emitters/default-event-emitter.hh>
#include <events/listeners/application-event-listener.hh>

namespace brasio::events::emitters
{
    class ApplicationEventEmitter : public DefaultEventEmitter
    {
    public:
        virtual void fire(subevents::ApplicationRenderEvent &event) override;
        virtual void fire(subevents::ApplicationTickEvent &event) override;
        virtual void fire(subevents::ApplicationUpdateEvent &event) override;

        void addListener(listeners::ApplicationEventListener &listener);

    private:
        std::vector<std::reference_wrapper<listeners::ApplicationEventListener>>
            _listeners;
    };
} // namespace brasio::events::emitters
