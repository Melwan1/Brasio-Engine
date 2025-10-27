#include <events/subevents/keyboard-press.hh>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

KeyboardPressEvent::KeyboardPressEvent(const std::string &pressedKey)
    : KeyboardCategoryEvent<KeyboardPressEvent>(EVENT_KEYBOARD_PRESS)
    , _pressedKey(pressedKey)
{}

const std::string &KeyboardPressEvent::getPressedKey() const
{
    return _pressedKey;
}

static bool generateUppercase(int mods)
{
    return ((mods & GLFW_MOD_SHIFT) != 0) ^ ((mods & GLFW_MOD_CAPS_LOCK) != 0);
}

// condition handlers

std::function<bool(int, int, int)>
    KeyboardPressEvent::conditionLowercaseLetters =
        [](int key, int, int mods) -> bool {
    return !generateUppercase(mods) && (key >= GLFW_KEY_A && key <= GLFW_KEY_Z);
};

std::function<bool(int, int, int)>
    KeyboardPressEvent::conditionUppercaseLetters =
        [](int key, int, int mods) -> bool {
    return generateUppercase(mods) && (key >= GLFW_KEY_A && key <= GLFW_KEY_Z);
};

std::function<bool(int, int, int)> KeyboardPressEvent::conditionDigits =
    [](int key, int, int mods) -> bool {
    return generateUppercase(mods) && (key >= GLFW_KEY_0 && key <= GLFW_KEY_9);
};

std::function<bool(int, int, int)> KeyboardPressEvent::conditionNumpadDigits =
    [](int key, int, int mods) -> bool {
    return (mods & GLFW_MOD_NUM_LOCK)
        && (key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_9);
};

std::function<bool(int, int, int)> KeyboardPressEvent::conditionFunctions =
    [](int key, int, int) -> bool {
    return key >= GLFW_KEY_F1 && key <= GLFW_KEY_F12;
};

// key generators

std::function<std::string(int, int, int)>
    KeyboardPressEvent::keyGeneratorLowercaseLetters =
        [](int key, int, int) -> std::string {
    std::cout << "generating a lowercase letter!" << std::endl;
    char c = key - GLFW_KEY_A + 'a';
    return { 1, c };
};

std::function<std::string(int, int, int)>
    KeyboardPressEvent::keyGeneratorUppercaseLetters =
        [](int key, int, int) -> std::string {
    std::cout << "generating an uppercase letter!" << std::endl;
    char c = key - GLFW_KEY_A + 'A';
    return { 1, c };
};

std::function<std::string(int, int, int)>
    KeyboardPressEvent::keyGeneratorDigits =
        [](int key, int, int) -> std::string {
    std::cout << "generating a classic digit!" << std::endl;
    char c = key - GLFW_KEY_0 + '0';
    return { 1, c };
};

std::function<std::string(int, int, int)>
    KeyboardPressEvent::keyGeneratorNumpadDigits =
        [](int key, int, int) -> std::string {
    std::cout << "generating a numpad digit!" << std::endl;
    char c = key - GLFW_KEY_KP_0 + '0';
    return { 1, c };
};

std::function<std::string(int, int, int)>
    KeyboardPressEvent::keyGeneratorFunctions =
        [](int key, int, int) -> std::string {
    std::cout << "generating a function key!" << std::endl;
    int functionKey = key - GLFW_KEY_F1 + 1;
    std::ostringstream oss;
    oss << 'F' << functionKey;
    return oss.str();
};

const KeyboardPressEvent::Handler KeyboardPressEvent::_handlers[] = {
    { .condition = conditionLowercaseLetters,
      .keyGenerator = keyGeneratorLowercaseLetters },
    { .condition = conditionUppercaseLetters,
      .keyGenerator = keyGeneratorUppercaseLetters },
    { .condition = conditionDigits, .keyGenerator = keyGeneratorDigits },
    { .condition = conditionNumpadDigits,
      .keyGenerator = keyGeneratorNumpadDigits },
    { .condition = conditionFunctions, .keyGenerator = keyGeneratorFunctions },
};

KeyboardPressEvent KeyboardPressEvent::create(int key, int scancode, int mods)
{
    std::cout << "Creating KeyboardPressEvent with key: " << key
              << " with modifiers: " << mods << std::endl;
    for (const auto &handler : _handlers)
    {
        if (handler.condition(key, scancode, mods))
        {
            std::string pressedKey = handler.keyGenerator(key, scancode, mods);
            KeyboardPressEvent event(pressedKey);
            std::cout << "Name of key: " << event.getPressedKey() << std::endl;
            return event;
        }
    }
    // should not go here
    std::string pressedKey = "";
    KeyboardPressEvent event(pressedKey);
    return event;
}
