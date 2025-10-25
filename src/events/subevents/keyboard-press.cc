#include <events/subevents/keyboard-press.hh>

KeyboardPressEvent::KeyboardPressEvent(char pressedKey)
    : KeyboardCategoryEvent<KeyboardPressEvent>(EVENT_KEYBOARD_PRESS)
    , _pressedKey(pressedKey)
{}

char KeyboardPressEvent::getPressedKey() const
{
    return _pressedKey;
}
