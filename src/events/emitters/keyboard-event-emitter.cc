#include <events/emitters/keyboard-event-emitter.hh>

namespace brasio::events::emitters
{
    void KeyboardEventEmitter::addListener(
        listeners::KeyboardEventListener &listener)
    {
        _listeners.push_back(listener);
    }

    void KeyboardEventEmitter::fire(subevents::KeyboardPressEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }

    void KeyboardEventEmitter::fire(subevents::KeyboardLongPressEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }

    void KeyboardEventEmitter::fire(subevents::KeyboardReleaseEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }
} // namespace brasio::events::emitters
