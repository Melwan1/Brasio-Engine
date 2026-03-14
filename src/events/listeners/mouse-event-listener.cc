#include <events/listeners/mouse-event-listener.hh>

namespace brasio::events::listeners
{
    void MouseEventListener::onEvent(subevents::MouseClickEvent &)
    {}

    void MouseEventListener::onEvent(subevents::MouseMoveEvent &)
    {}

    void MouseEventListener::onEvent(subevents::MouseReleaseEvent &)
    {}

    void MouseEventListener::onEvent(subevents::MouseScrollEvent &)
    {}
} // namespace brasio::events::listeners
