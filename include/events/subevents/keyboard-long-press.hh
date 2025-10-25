#pragma once

#include <events/libevents.hh>

class KeyboardLongPressEvent
    : public KeyboardCategoryEvent<KeyboardLongPressEvent>
{
public:
    KeyboardLongPressEvent(char pressedKey, unsigned numPresses);

    char getPressedKey() const;
    unsigned getNumPresses() const;

private:
    char _pressedKey;
    unsigned _numPresses;
};
