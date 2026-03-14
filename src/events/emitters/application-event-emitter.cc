#include <events/emitters/application-event-emitter.hh>

namespace brasio::events::emitters
{
    void ApplicationEventEmitter::addListener(
        listeners::ApplicationEventListener &listener)
    {
        _listeners.push_back(listener);
    }

    void ApplicationEventEmitter::fire(subevents::ApplicationRenderEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }

    void ApplicationEventEmitter::fire(subevents::ApplicationTickEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }

    void ApplicationEventEmitter::fire(subevents::ApplicationUpdateEvent &event)
    {
        std::for_each(
            _listeners.begin(), _listeners.end(),
            [&event](auto &listener) { listener.get().onEvent(event); });
    }
} // namespace brasio::events::emitters
