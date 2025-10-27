#include <events/subevents/keyboard-long-press.hh>

KeyboardLongPressEvent::KeyboardLongPressEvent(const std::string &pressedKey,
                                               unsigned numPresses)
    : KeyboardCategoryEvent<KeyboardLongPressEvent>(EVENT_KEYBOARD_LONG_PRESS)
    , _pressedKey(pressedKey)
    , _numPresses(numPresses)
{}

const std::string &KeyboardLongPressEvent::getPressedKey() const
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
    const std::string pressedKey = "A";
    unsigned numPresses = 1;
    KeyboardLongPressEvent event(pressedKey, numPresses);
    return event;
}
