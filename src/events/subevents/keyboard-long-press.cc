#include <events/subevents/keyboard-long-press.hh>

KeyboardLongPressEvent::KeyboardLongPressEvent(char pressedKey,
                                               unsigned numPresses)
    : KeyboardCategoryEvent<KeyboardLongPressEvent>(EVENT_KEYBOARD_LONG_PRESS)
    , _pressedKey(pressedKey)
    , _numPresses(numPresses)
{}

char KeyboardLongPressEvent::getPressedKey() const
{
    return _pressedKey;
}

unsigned KeyboardLongPressEvent::getNumPresses() const
{
    return _numPresses;
}
