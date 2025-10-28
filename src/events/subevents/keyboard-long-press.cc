#include <events/subevents/keyboard-long-press.hh>

#include <events/subevents/key-generator.hh>

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
    std::string pressedKey = KeyGenerator::generate(key, scancode, mods);
    KeyboardLongPressEvent event(pressedKey, 1);
    return event;
}

void KeyboardLongPressEvent::print(std::ostream &ostr)
{
    Event::print(ostr);
    ostr << FG_ESC(220) << " " << getPressedKey() << ESC_RESET << "\n";
}
