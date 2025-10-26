#include <events/emitters/application-event-emitter.hh>

void ApplicationEventEmitter::addListener(ApplicationEventListener &listener)
{
    _listeners.push_back(listener);
}

void ApplicationEventEmitter::fire(ApplicationRenderEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}

void ApplicationEventEmitter::fire(ApplicationTickEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}

void ApplicationEventEmitter::fire(ApplicationUpdateEvent &event)
{
    std::for_each(_listeners.begin(), _listeners.end(),
                  [&event](auto &listener) { listener.get().onEvent(event); });
}
