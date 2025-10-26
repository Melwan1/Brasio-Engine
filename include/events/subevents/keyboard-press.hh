#pragma once

#include <events/categories/categories.hh>

#include <functional>

class KeyboardPressEvent : public KeyboardCategoryEvent<KeyboardPressEvent>
{
public:
    KeyboardPressEvent(char pressedKey);
    char getPressedKey() const;

    static KeyboardPressEvent create(int key, int scancode, int mods);

private:
    char _pressedKey;

    struct Handler
    {
        std::function<bool(int, int, int)> condition;
        std::function<char(int, int, int)> keyGenerator;
    };

    // condition handlers

    static std::function<bool(int, int, int)> conditionLowercaseLetters;
    static std::function<bool(int, int, int)> conditionUppercaseLetters;
    static std::function<bool(int, int, int)> conditionDigits;
    static std::function<bool(int, int, int)> conditionNumpadDigits;

    // key generators

    static std::function<char(int, int, int)> keyGeneratorLowercaseLetters;
    static std::function<char(int, int, int)> keyGeneratorUppercaseLetters;
    static std::function<char(int, int, int)> keyGeneratorDigits;
    static std::function<char(int, int, int)> keyGeneratorNumpadDigits;

    const static Handler _handlers[];
};
