#include <events/listeners/keyboard-event-listeners.hh>

#include <iostream>

void KeyboardEventListener::onEvent(KeyboardLongPressEvent &)
{
    std::cout << "Got a KeyLongPress event!" << std::endl;
}

void KeyboardEventListener::onEvent(KeyboardPressEvent &)
{
    std::cout << "Got a KeyPress event!" << std::endl;
}

void KeyboardEventListener::onEvent(KeyboardReleaseEvent &)
{
    std::cout << "Got a KeyRelease event!" << std::endl;
}
