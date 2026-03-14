#include <events/emitters/window-event-emitter.hh>

namespace brasio::events::emitters
{
    void
    WindowEventEmitter::addListener(listeners::WindowEventListener &listener)
    {
        _listeners.push_back(listener);
    }

    void WindowEventEmitter::fire(subevents::WindowCloseEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }

    void WindowEventEmitter::fire(subevents::WindowFocusEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }

    void WindowEventEmitter::fire(subevents::WindowLostFocusEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }

    void WindowEventEmitter::fire(subevents::WindowMoveEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }

    void WindowEventEmitter::fire(subevents::WindowResizeEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }
} // namespace brasio::events::emitters
