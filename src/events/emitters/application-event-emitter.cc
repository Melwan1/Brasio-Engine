#include <events/emitters/application-event-emitter.hh>

void ApplicationEventEmitter::fire(ApplicationRenderEvent &)
{}

void ApplicationEventEmitter::fire(ApplicationTickEvent &)
{}

void ApplicationEventEmitter::fire(ApplicationUpdateEvent &)
{}
