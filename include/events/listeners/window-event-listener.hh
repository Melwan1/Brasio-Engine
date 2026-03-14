#pragma once

#include <events/listeners/default-event-listener.hh>

namespace brasio::events::listeners
{

    class WindowEventListener : public DefaultEventListener
    {
    public:
        virtual void onEvent(subevents::WindowCloseEvent &) override;
        virtual void onEvent(subevents::WindowFocusEvent &) override;
        virtual void onEvent(subevents::WindowLostFocusEvent &) override;
        virtual void onEvent(subevents::WindowMoveEvent &) override;
        virtual void onEvent(subevents::WindowResizeEvent &) override;
    };
} // namespace brasio::events::listeners
