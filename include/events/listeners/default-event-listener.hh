#pragma once

#include <events/listeners/event-listener.hh>

namespace brasio::events::listeners
{
    class DefaultEventListener : public EventListener
    {
    public:
        virtual void onEvent(subevents::ApplicationRenderEvent &) override;
        virtual void onEvent(subevents::ApplicationTickEvent &) override;
        virtual void onEvent(subevents::ApplicationUpdateEvent &) override;
        virtual void onEvent(subevents::KeyboardLongPressEvent &) override;
        virtual void onEvent(subevents::KeyboardPressEvent &) override;
        virtual void onEvent(subevents::KeyboardReleaseEvent &) override;
        virtual void onEvent(subevents::MouseClickEvent &) override;
        virtual void onEvent(subevents::MouseMoveEvent &) override;
        virtual void onEvent(subevents::MouseReleaseEvent &) override;
        virtual void onEvent(subevents::MouseScrollEvent &) override;
        virtual void onEvent(subevents::UnknownEvent &) override;
        virtual void onEvent(subevents::WindowCloseEvent &) override;
        virtual void onEvent(subevents::WindowFocusEvent &) override;
        virtual void onEvent(subevents::WindowLostFocusEvent &) override;
        virtual void onEvent(subevents::WindowMoveEvent &) override;
        virtual void onEvent(subevents::WindowResizeEvent &) override;
    };
} // namespace brasio::events::listeners
