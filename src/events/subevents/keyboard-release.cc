#include <events/subevents/keyboard-release.hh>

KeyboardReleaseEvent::KeyboardReleaseEvent(char pressedKey)
    : KeyboardCategoryEvent<KeyboardReleaseEvent>(EVENT_KEYBOARD_RELEASE)
    , _pressedKey(pressedKey)
{}

char KeyboardReleaseEvent::getPressedKey() const
{
    return _pressedKey;
}
