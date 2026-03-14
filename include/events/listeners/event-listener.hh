#pragma once

#include <events/subevents/subevents.hh>

namespace brasio::events::listeners
{
    class EventListener
    {
    public:
        virtual ~EventListener() = default;
        virtual void onEvent(subevents::ApplicationRenderEvent &) = 0;
        virtual void onEvent(subevents::ApplicationTickEvent &) = 0;
        virtual void onEvent(subevents::ApplicationUpdateEvent &) = 0;
        virtual void onEvent(subevents::KeyboardLongPressEvent &) = 0;
        virtual void onEvent(subevents::KeyboardPressEvent &) = 0;
        virtual void onEvent(subevents::KeyboardReleaseEvent &) = 0;
        virtual void onEvent(subevents::MouseClickEvent &) = 0;
        virtual void onEvent(subevents::MouseMoveEvent &) = 0;
        virtual void onEvent(subevents::MouseReleaseEvent &) = 0;
        virtual void onEvent(subevents::MouseScrollEvent &) = 0;
        virtual void onEvent(subevents::UnknownEvent &) = 0;
        virtual void onEvent(subevents::WindowCloseEvent &) = 0;
        virtual void onEvent(subevents::WindowFocusEvent &) = 0;
        virtual void onEvent(subevents::WindowLostFocusEvent &) = 0;
        virtual void onEvent(subevents::WindowMoveEvent &) = 0;
        virtual void onEvent(subevents::WindowResizeEvent &) = 0;
    };
} // namespace brasio::events::listeners
