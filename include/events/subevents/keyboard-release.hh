#pragma once

#include <events/categories/categories.hh>

class KeyboardReleaseEvent : public KeyboardCategoryEvent<KeyboardReleaseEvent>
{
public:
    KeyboardReleaseEvent(char pressedKey);

    char getPressedKey() const;

private:
    char _pressedKey;
};
