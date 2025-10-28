#pragma once

#include <functional>
#include <string>

class KeyGenerator
{
public:
    static std::string generate(int key, int scancode, int mods);

private:
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
    static std::function<bool(int, int, int)> conditionFunctions;
    static std::function<bool(int, int, int)> conditionEscape;

    // key generators

    static std::function<std::string(int, int, int)>
        keyGeneratorLowercaseLetters;
    static std::function<std::string(int, int, int)>
        keyGeneratorUppercaseLetters;
    static std::function<std::string(int, int, int)> keyGeneratorDigits;
    static std::function<std::string(int, int, int)> keyGeneratorNumpadDigits;
    static std::function<std::string(int, int, int)> keyGeneratorFunctions;
    static std::function<std::string(int, int, int)> keyGeneratorEscape;

    const static Handler _handlers[];
};
