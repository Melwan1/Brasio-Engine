#include <events/emitters/mouse-event-emitter.hh>

namespace brasio::events::emitters
{
    void MouseEventEmitter::addListener(listeners::MouseEventListener &listener)
    {
        _listeners.push_back(listener);
    }

    void MouseEventEmitter::fire(subevents::MouseClickEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }

    void MouseEventEmitter::fire(subevents::MouseMoveEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }

    void MouseEventEmitter::fire(subevents::MouseReleaseEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }

    void MouseEventEmitter::fire(subevents::MouseScrollEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }
} // namespace brasio::events::emitters
