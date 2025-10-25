#include <events/emitters/window-event-emitter.hh>

void WindowEventEmitter::fire(WindowCloseEvent &)
{}

void WindowEventEmitter::fire(WindowFocusEvent &)
{}

void WindowEventEmitter::fire(WindowLostFocusEvent &)
{}

void WindowEventEmitter::fire(WindowMoveEvent &)
{}

void WindowEventEmitter::fire(WindowResizeEvent &)
{}
