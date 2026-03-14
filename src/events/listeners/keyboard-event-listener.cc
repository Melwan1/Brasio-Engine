#include <events/listeners/keyboard-event-listeners.hh>

#include <iostream>

namespace brasio::events::listeners
{
    void
    KeyboardEventListener::onEvent(subevents::KeyboardLongPressEvent &event)
    {
        event.print(std::cout);
        event.handle();
    }

    void KeyboardEventListener::onEvent(subevents::KeyboardPressEvent &event)
    {
        event.print(std::cout);
        event.handle();
    }

    void KeyboardEventListener::onEvent(subevents::KeyboardReleaseEvent &event)
    {
        event.print(std::cout);
        event.handle();
    }
} // namespace brasio::events::listeners
