#pragma once

#include <events/subevents/subevents.hh>

namespace brasio::events::emitters
{
    class EventEmitter
    {
    public:
        virtual void fire(subevents::ApplicationRenderEvent &) = 0;
        virtual void fire(subevents::ApplicationTickEvent &) = 0;
        virtual void fire(subevents::ApplicationUpdateEvent &) = 0;
        virtual void fire(subevents::KeyboardLongPressEvent &) = 0;
        virtual void fire(subevents::KeyboardPressEvent &) = 0;
        virtual void fire(subevents::KeyboardReleaseEvent &) = 0;
        virtual void fire(subevents::MouseClickEvent &) = 0;
        virtual void fire(subevents::MouseMoveEvent &) = 0;
        virtual void fire(subevents::MouseReleaseEvent &) = 0;
        virtual void fire(subevents::MouseScrollEvent &) = 0;
        virtual void fire(subevents::UnknownEvent &) = 0;
        virtual void fire(subevents::WindowCloseEvent &) = 0;
        virtual void fire(subevents::WindowFocusEvent &) = 0;
        virtual void fire(subevents::WindowLostFocusEvent &) = 0;
        virtual void fire(subevents::WindowMoveEvent &) = 0;
        virtual void fire(subevents::WindowResizeEvent &) = 0;
    };
} // namespace brasio::events::emitters
