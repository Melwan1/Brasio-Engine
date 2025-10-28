#pragma once

#include <events/categories/categories.hh>

#include <functional>

class KeyboardPressEvent : public KeyboardCategoryEvent<KeyboardPressEvent>
{
public:
    KeyboardPressEvent(const std::string &pressedKey);
    const std::string &getPressedKey() const;

    static KeyboardPressEvent create(int key, int scancode, int mods);

    virtual std::string getTypeName() const override
    {
        return "KeyboardPressEvent";
    }

private:
    std::string _pressedKey;
};
