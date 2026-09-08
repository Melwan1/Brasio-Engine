#include <events/subevents/keyboard-release.hh>

#include <events/key-generator.hh>

namespace brasio::events::subevents
{
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
        const std::string pressedKey =
            KeyGenerator::generate(key, scancode, mods);
        KeyboardReleaseEvent event(pressedKey);
        return event;
    }

} // namespace brasio::events::subevents
