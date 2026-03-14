#include <events/listeners/default-event-listener.hh>

namespace brasio::events::listeners
{
    void DefaultEventListener::onEvent(subevents::ApplicationRenderEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::ApplicationTickEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::ApplicationUpdateEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::KeyboardLongPressEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::KeyboardPressEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::KeyboardReleaseEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::MouseClickEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::MouseMoveEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::MouseReleaseEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::MouseScrollEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::UnknownEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::WindowCloseEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::WindowFocusEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::WindowLostFocusEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::WindowMoveEvent &)
    {}

    void DefaultEventListener::onEvent(subevents::WindowResizeEvent &)
    {}
} // namespace brasio::events::listeners
