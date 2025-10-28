#include <events/listeners/window-event-listener.hh>

#include <iostream>

void WindowEventListener::onEvent(WindowCloseEvent &event)
{
    event.print(std::cout);
    event.handle();
}

void WindowEventListener::onEvent(WindowFocusEvent &event)
{
    event.print(std::cout);
    event.handle();
}

void WindowEventListener::onEvent(WindowLostFocusEvent &event)
{
    event.print(std::cout);
    event.handle();
}

void WindowEventListener::onEvent(WindowMoveEvent &event)
{
    event.print(std::cout);
    event.handle();
}

void WindowEventListener::onEvent(WindowResizeEvent &event)
{
    event.print(std::cout);
    event.handle();
}
