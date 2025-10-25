#include <events/subevents/keyboard-press.hh>

KeyboardPressEvent::KeyboardPressEvent(char pressedKey)
    : KeyboardCategoryEvent<KeyboardPressEvent>(EVENT_KEYBOARD_PRESS)
    , _pressedKey(pressedKey)
{}

char KeyboardPressEvent::getPressedKey() const
{
    return _pressedKey;
}

KeyboardPressEvent KeyboardPressEvent::create(int key, int scancode, int mods)
{
    (void)key;
    (void)scancode;
    (void)mods;
    char pressedKey = 'A';
    KeyboardPressEvent event(pressedKey);
    return event;
}
