#pragma once

#include <events/libevents.hh>

class KeyboardReleaseEvent : public KeyboardCategoryEvent<KeyboardReleaseEvent>
{
public:
    KeyboardReleaseEvent(char pressedKey);

    char getPressedKey() const;

private:
    char _pressedKey;
};
