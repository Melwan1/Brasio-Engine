#include <events/subevents/keyboard-release.hh>

#include <events/key-generator.hh>

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
    const std::string pressedKey = KeyGenerator::generate(key, scancode, mods);
    KeyboardReleaseEvent event(pressedKey);
    return event;
}

void KeyboardReleaseEvent::print(std::ostream &ostr)
{
    Event::print(ostr);
    ostr << FG_ESC(220) << " " << getPressedKey() << ESC_RESET << "\n";
}
