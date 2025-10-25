#pragma once

#include <events/categories/categories.hh>

class KeyboardPressEvent : public KeyboardCategoryEvent<KeyboardPressEvent>
{
public:
    KeyboardPressEvent(char pressedKey);
    char getPressedKey() const;

private:
    char _pressedKey;
};
