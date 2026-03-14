#pragma once

#include <events/listeners/default-event-listener.hh>

namespace brasio::events::listeners
{

    class KeyboardEventListener : public DefaultEventListener
    {
    public:
        virtual void onEvent(subevents::KeyboardLongPressEvent &) override;
        virtual void onEvent(subevents::KeyboardPressEvent &) override;
        virtual void onEvent(subevents::KeyboardReleaseEvent &) override;
    };
} // namespace brasio::events::listeners
