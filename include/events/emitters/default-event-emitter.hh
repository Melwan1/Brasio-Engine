#pragma once

#include <events/emitters/event-emitter.hh>

namespace brasio::events::emitters
{
    class DefaultEventEmitter : public EventEmitter
    {
    public:
        virtual void fire(subevents::ApplicationRenderEvent &) override;
        virtual void fire(subevents::ApplicationTickEvent &) override;
        virtual void fire(subevents::ApplicationUpdateEvent &) override;
        virtual void fire(subevents::KeyboardLongPressEvent &) override;
        virtual void fire(subevents::KeyboardPressEvent &) override;
        virtual void fire(subevents::KeyboardReleaseEvent &) override;
        virtual void fire(subevents::MouseClickEvent &) override;
        virtual void fire(subevents::MouseMoveEvent &) override;
        virtual void fire(subevents::MouseReleaseEvent &) override;
        virtual void fire(subevents::MouseScrollEvent &) override;
        virtual void fire(subevents::UnknownEvent &) override;
        virtual void fire(subevents::WindowCloseEvent &) override;
        virtual void fire(subevents::WindowFocusEvent &) override;
        virtual void fire(subevents::WindowLostFocusEvent &) override;
        virtual void fire(subevents::WindowMoveEvent &) override;
        virtual void fire(subevents::WindowResizeEvent &) override;
    };
} // namespace brasio::events::emitters
