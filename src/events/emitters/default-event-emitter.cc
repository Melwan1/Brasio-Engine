#include <events/emitters/default-event-emitter.hh>

void DefaultEventEmitter::fire(ApplicationRenderEvent &)
{}

void DefaultEventEmitter::fire(ApplicationTickEvent &)
{}

void DefaultEventEmitter::fire(ApplicationUpdateEvent &)
{}

void DefaultEventEmitter::fire(KeyboardLongPressEvent &)
{}

void DefaultEventEmitter::fire(KeyboardPressEvent &)
{}

void DefaultEventEmitter::fire(KeyboardReleaseEvent &)
{}

void DefaultEventEmitter::fire(MouseClickEvent &)
{}

void DefaultEventEmitter::fire(MouseMoveEvent &)
{}

void DefaultEventEmitter::fire(MouseReleaseEvent &)
{}

void DefaultEventEmitter::fire(MouseScrollEvent &)
{}

void DefaultEventEmitter::fire(UnknownEvent &)
{}

void DefaultEventEmitter::fire(WindowCloseEvent &)
{}

void DefaultEventEmitter::fire(WindowFocusEvent &)
{}

void DefaultEventEmitter::fire(WindowLostFocusEvent &)
{}

void DefaultEventEmitter::fire(WindowMoveEvent &)
{}

void DefaultEventEmitter::fire(WindowResizeEvent &)
{}
