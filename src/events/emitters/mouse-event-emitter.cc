#include <events/emitters/mouse-event-emitter.hh>

void MouseEventEmitter::addListener(MouseEventListener &listener)
{
    _listeners.push_back(listener);
}

void MouseEventEmitter::fire(MouseClickEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}

void MouseEventEmitter::fire(MouseMoveEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}

void MouseEventEmitter::fire(MouseReleaseEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}

void MouseEventEmitter::fire(MouseScrollEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}
