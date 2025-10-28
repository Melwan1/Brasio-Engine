#include <events/subevents/keyboard-press.hh>

#include <events/key-generator.hh>

KeyboardPressEvent::KeyboardPressEvent(const std::string &pressedKey)
    : KeyboardCategoryEvent<KeyboardPressEvent>(EVENT_KEYBOARD_PRESS)
    , _pressedKey(pressedKey)
{}

const std::string &KeyboardPressEvent::getPressedKey() const
{
    return _pressedKey;
}

KeyboardPressEvent KeyboardPressEvent::create(int key, int scancode, int mods)
{
    std::string pressedKey = KeyGenerator::generate(key, scancode, mods);
    KeyboardPressEvent event(pressedKey);
    return event;
}

void KeyboardPressEvent::print(std::ostream &ostr)
{
    Event::print(ostr);
    ostr << FG_ESC(220) << " " << getPressedKey() << ESC_RESET << "\n";
}
