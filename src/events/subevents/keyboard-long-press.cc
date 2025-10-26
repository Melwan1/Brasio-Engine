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

KeyboardLongPressEvent KeyboardLongPressEvent::create(int key, int scancode,
                                                      int mods)
{
    (void)key;
    (void)scancode;
    (void)mods;
    char pressedKey = 'A';
    unsigned numPresses = 1;
    KeyboardLongPressEvent event(pressedKey, numPresses);
    return event;
}
