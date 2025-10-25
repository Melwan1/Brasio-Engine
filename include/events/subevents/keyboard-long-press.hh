#pragma once

#include <events/categories/categories.hh>

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
