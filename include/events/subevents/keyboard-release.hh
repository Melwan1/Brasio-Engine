#pragma once

#include <events/categories/categories.hh>

class KeyboardReleaseEvent : public KeyboardCategoryEvent<KeyboardReleaseEvent>
{
public:
    KeyboardReleaseEvent(const std::string &pressedKey);

    const std::string &getPressedKey() const;

    static KeyboardReleaseEvent create(int key, int scancode, int mods);

    virtual std::string getTypeName() const override
    {
        return "KeyboardReleaseEvent";
    }

private:
    std::string _pressedKey;
};
