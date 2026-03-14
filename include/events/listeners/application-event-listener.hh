#pragma once

#include <events/listeners/default-event-listener.hh>

namespace brasio::events::listeners
{
    class ApplicationEventListener : public DefaultEventListener
    {
    public:
        virtual void onEvent(subevents::ApplicationRenderEvent &) override;
        virtual void onEvent(subevents::ApplicationTickEvent &) override;
        virtual void onEvent(subevents::ApplicationUpdateEvent &) override;
    };
} // namespace brasio::events::listeners
