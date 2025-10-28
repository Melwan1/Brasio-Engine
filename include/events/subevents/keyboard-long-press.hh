#pragma once

#include <events/categories/categories.hh>

class KeyboardLongPressEvent
    : public KeyboardCategoryEvent<KeyboardLongPressEvent>
{
public:
    KeyboardLongPressEvent(const std::string &pressedKey, unsigned numPresses);

    const std::string &getPressedKey() const;
    unsigned getNumPresses() const;

    static KeyboardLongPressEvent create(int key, int scancode, int mods);

    virtual std::string getTypeName() const override
    {
        return "KeyboardLongPressEvent";
    }

    virtual void print(std::ostream &ostr) override;

private:
    std::string _pressedKey;
    unsigned _numPresses;
};
