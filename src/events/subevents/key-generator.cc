#include <events/subevents/key-generator.hh>

#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static bool generateUppercase(int mods)
{
    return ((mods & GLFW_MOD_SHIFT) != 0) ^ ((mods & GLFW_MOD_CAPS_LOCK) != 0);
}

// condition handlers

std::function<bool(int, int, int)> KeyGenerator::conditionLowercaseLetters =
    [](int key, int, int mods) -> bool {
    return !generateUppercase(mods) && (key >= GLFW_KEY_A && key <= GLFW_KEY_Z);
};

std::function<bool(int, int, int)> KeyGenerator::conditionUppercaseLetters =
    [](int key, int, int mods) -> bool {
    return generateUppercase(mods) && (key >= GLFW_KEY_A && key <= GLFW_KEY_Z);
};

std::function<bool(int, int, int)> KeyGenerator::conditionDigits =
    [](int key, int, int mods) -> bool {
    return generateUppercase(mods) && (key >= GLFW_KEY_0 && key <= GLFW_KEY_9);
};

std::function<bool(int, int, int)> KeyGenerator::conditionNumpadDigits =
    [](int key, int, int mods) -> bool {
    return (mods & GLFW_MOD_NUM_LOCK)
        && (key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_9);
};

std::function<bool(int, int, int)> KeyGenerator::conditionFunctions =
    [](int key, int, int) -> bool {
    return key >= GLFW_KEY_F1 && key <= GLFW_KEY_F12;
};

std::function<bool(int, int, int)> KeyGenerator::conditionEscape =
    [](int key, int, int) -> bool { return key == GLFW_KEY_ESCAPE; };

// key generators

std::function<std::string(int, int, int)>
    KeyGenerator::keyGeneratorLowercaseLetters =
        [](int key, int, int) -> std::string {
    char c = key - GLFW_KEY_A + 'a';
    return { 1, c };
};

std::function<std::string(int, int, int)>
    KeyGenerator::keyGeneratorUppercaseLetters =
        [](int key, int, int) -> std::string {
    char c = key - GLFW_KEY_A + 'A';
    return { 1, c };
};

std::function<std::string(int, int, int)> KeyGenerator::keyGeneratorDigits =
    [](int key, int, int) -> std::string {
    char c = key - GLFW_KEY_0 + '0';
    return { 1, c };
};

std::function<std::string(int, int, int)>
    KeyGenerator::keyGeneratorNumpadDigits =
        [](int key, int, int) -> std::string {
    char c = key - GLFW_KEY_KP_0 + '0';
    return { 1, c };
};

std::function<std::string(int, int, int)> KeyGenerator::keyGeneratorFunctions =
    [](int key, int, int) -> std::string {
    int functionKey = key - GLFW_KEY_F1 + 1;
    std::ostringstream oss;
    oss << 'F' << functionKey;
    return oss.str();
};

std::function<std::string(int, int, int)> KeyGenerator::keyGeneratorEscape =
    [](int, int, int) -> std::string { return "ESC"; };

const KeyGenerator::Handler KeyGenerator::_handlers[] = {
    { .condition = conditionLowercaseLetters,
      .keyGenerator = keyGeneratorLowercaseLetters },
    { .condition = conditionUppercaseLetters,
      .keyGenerator = keyGeneratorUppercaseLetters },
    { .condition = conditionDigits, .keyGenerator = keyGeneratorDigits },
    { .condition = conditionNumpadDigits,
      .keyGenerator = keyGeneratorNumpadDigits },
    { .condition = conditionFunctions, .keyGenerator = keyGeneratorFunctions },
    { .condition = conditionEscape, .keyGenerator = keyGeneratorEscape },
};

std::string KeyGenerator::generate(int key, int scancode, int mods)
{
    for (const auto &handler : _handlers)
    {
        if (handler.condition(key, scancode, mods))
        {
            return handler.keyGenerator(key, scancode, mods);
        }
    }
    // should not go here
    return "<Unknown key>";
}
