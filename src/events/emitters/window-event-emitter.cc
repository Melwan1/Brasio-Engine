#include <events/emitters/window-event-emitter.hh>

void WindowEventEmitter::addListener(WindowEventListener &listener)
{
    _listeners.push_back(listener);
}

void WindowEventEmitter::fire(WindowCloseEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}

void WindowEventEmitter::fire(WindowFocusEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}

void WindowEventEmitter::fire(WindowLostFocusEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}

void WindowEventEmitter::fire(WindowMoveEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}

void WindowEventEmitter::fire(WindowResizeEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}
