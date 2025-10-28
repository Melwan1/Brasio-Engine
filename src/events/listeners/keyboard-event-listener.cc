#include <events/listeners/keyboard-event-listeners.hh>

#include <iostream>

void KeyboardEventListener::onEvent(KeyboardLongPressEvent &event)
{
    event.print(std::cout);
    event.handle();
}

void KeyboardEventListener::onEvent(KeyboardPressEvent &event)
{
    event.print(std::cout);
    event.handle();
}

void KeyboardEventListener::onEvent(KeyboardReleaseEvent &event)
{
    event.print(std::cout);
    event.handle();
}
