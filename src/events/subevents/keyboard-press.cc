#include <events/subevents/keyboard-press.hh>

KeyboardPressEvent::KeyboardPressEvent()
    : KeyboardCategoryEvent<KeyboardPressEvent>(EVENT_KEYBOARD_PRESS)
{}
