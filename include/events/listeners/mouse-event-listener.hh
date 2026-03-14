#pragma once

#include <events/listeners/default-event-listener.hh>

namespace brasio::events::listeners
{

    class MouseEventListener : public DefaultEventListener
    {
    public:
        virtual void onEvent(subevents::MouseClickEvent &) override;
        virtual void onEvent(subevents::MouseMoveEvent &) override;
        virtual void onEvent(subevents::MouseReleaseEvent &) override;
        virtual void onEvent(subevents::MouseScrollEvent &) override;
    };
} // namespace brasio::events::listeners
