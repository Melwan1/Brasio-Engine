#include <events/subevents/keyboard-release.hh>

KeyboardReleaseEvent::KeyboardReleaseEvent(const std::string &pressedKey)
    : KeyboardCategoryEvent<KeyboardReleaseEvent>(EVENT_KEYBOARD_RELEASE)
    , _pressedKey(pressedKey)
{}

const std::string &KeyboardReleaseEvent::getPressedKey() const
{
    return _pressedKey;
}

KeyboardReleaseEvent KeyboardReleaseEvent::create(int key, int scancode,
                                                  int mods)
{
    (void)key;
    (void)scancode;
    (void)mods;
    const std::string pressedKey = "";
    KeyboardReleaseEvent event(pressedKey);
    return event;
}
