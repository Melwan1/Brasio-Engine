#include <events/emitters/keyboard-event-emitter.hh>

void KeyboardEventEmitter::addListener(KeyboardEventListener &listener)
{
    _listeners.push_back(listener);
}

void KeyboardEventEmitter::fire(KeyboardPressEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}

void KeyboardEventEmitter::fire(KeyboardLongPressEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}

void KeyboardEventEmitter::fire(KeyboardReleaseEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}
