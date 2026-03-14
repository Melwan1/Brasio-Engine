#include <events/emitters/default-event-emitter.hh>

namespace brasio::events::emitters
{
    void DefaultEventEmitter::fire(subevents::ApplicationRenderEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::ApplicationTickEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::ApplicationUpdateEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::KeyboardLongPressEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::KeyboardPressEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::KeyboardReleaseEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::MouseClickEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::MouseMoveEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::MouseReleaseEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::MouseScrollEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::UnknownEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::WindowCloseEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::WindowFocusEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::WindowLostFocusEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::WindowMoveEvent &)
    {}

    void DefaultEventEmitter::fire(subevents::WindowResizeEvent &)
    {}
} // namespace brasio::events::emitters
