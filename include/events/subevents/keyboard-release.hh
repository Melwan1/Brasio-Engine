#pragma once

#include <events/categories/categories.hh>

class KeyboardReleaseEvent : public KeyboardCategoryEvent<KeyboardReleaseEvent>
{
public:
    KeyboardReleaseEvent(char pressedKey);

    char getPressedKey() const;

    static KeyboardReleaseEvent create(int key, int scancode, int mods);

private:
    char _pressedKey;
};
