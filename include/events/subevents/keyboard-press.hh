#pragma once

#include <events/categories/categories.hh>

class KeyboardPressEvent : public KeyboardCategoryEvent<KeyboardPressEvent>
{
public:
    KeyboardPressEvent(char pressedKey);
    char getPressedKey() const;

    static KeyboardPressEvent create(int key, int scancode, int mods);

private:
    char _pressedKey;
};
