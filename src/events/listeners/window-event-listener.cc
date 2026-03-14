#include <events/listeners/window-event-listener.hh>

#include <iostream>

namespace brasio::events::listeners
{
    void WindowEventListener::onEvent(subevents::WindowCloseEvent &event)
    {
        event.print(std::cout);
        event.handle();
    }

    void WindowEventListener::onEvent(subevents::WindowFocusEvent &event)
    {
        event.print(std::cout);
        event.handle();
    }

    void WindowEventListener::onEvent(subevents::WindowLostFocusEvent &event)
    {
        event.print(std::cout);
        event.handle();
    }

    void WindowEventListener::onEvent(subevents::WindowMoveEvent &event)
    {
        event.print(std::cout);
        event.handle();
    }

    void WindowEventListener::onEvent(subevents::WindowResizeEvent &event)
    {
        event.print(std::cout);
        event.handle();
    }
} // namespace brasio::events::listeners
