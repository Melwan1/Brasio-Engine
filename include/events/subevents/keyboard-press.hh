#pragma once

#include <events/libevents.hh>

class KeyboardPressEvent : public KeyboardCategoryEvent<KeyboardPressEvent>
{
public:
    KeyboardPressEvent(char pressedKey);
    char getPressedKey() const;

private:
    char _pressedKey;
};
