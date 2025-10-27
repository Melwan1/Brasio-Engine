#pragma once

#include <events/categories/categories.hh>

#include <functional>

class KeyboardPressEvent : public KeyboardCategoryEvent<KeyboardPressEvent>
{
public:
    KeyboardPressEvent(const std::string &pressedKey);
    const std::string &getPressedKey() const;

    static KeyboardPressEvent create(int key, int scancode, int mods);

private:
    std::string _pressedKey;

    struct Handler
    {
        std::function<bool(int, int, int)> condition;
        std::function<std::string(int, int, int)> keyGenerator;
    };

    // condition handlers

    static std::function<bool(int, int, int)> conditionLowercaseLetters;
    static std::function<bool(int, int, int)> conditionUppercaseLetters;
    static std::function<bool(int, int, int)> conditionDigits;
    static std::function<bool(int, int, int)> conditionNumpadDigits;

    // key generators

    static std::function<std::string(int, int, int)>
        keyGeneratorLowercaseLetters;
    static std::function<std::string(int, int, int)>
        keyGeneratorUppercaseLetters;
    static std::function<std::string(int, int, int)> keyGeneratorDigits;
    static std::function<std::string(int, int, int)> keyGeneratorNumpadDigits;

    const static Handler _handlers[];
};
