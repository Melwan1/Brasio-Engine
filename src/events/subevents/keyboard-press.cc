#include <events/subevents/keyboard-press.hh>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

KeyboardPressEvent::KeyboardPressEvent(char pressedKey)
    : KeyboardCategoryEvent<KeyboardPressEvent>(EVENT_KEYBOARD_PRESS)
    , _pressedKey(pressedKey)
{}

char KeyboardPressEvent::getPressedKey() const
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

// key generators

std::function<char(int, int, int)>
    KeyboardPressEvent::keyGeneratorLowercaseLetters =
        [](int key, int, int) -> char {
    std::cout << "generating a lowercase letter!" << std::endl;
    return key - GLFW_KEY_A + 'a';
};

std::function<char(int, int, int)>
    KeyboardPressEvent::keyGeneratorUppercaseLetters =
        [](int key, int, int) -> bool {
    std::cout << "generating an uppercase letter!" << std::endl;
    return key - GLFW_KEY_A + 'A';
};

std::function<char(int, int, int)> KeyboardPressEvent::keyGeneratorDigits =
    [](int key, int, int) -> bool {
    std::cout << "generating a classic digit!" << std::endl;
    return key - GLFW_KEY_0 + '0';
};

std::function<char(int, int, int)>
    KeyboardPressEvent::keyGeneratorNumpadDigits =
        [](int key, int, int) -> bool {
    std::cout << "generating a numpad digit!" << std::endl;
    return key - GLFW_KEY_KP_0 + '0';
};

const KeyboardPressEvent::Handler KeyboardPressEvent::_handlers[] = {
    { .condition = conditionLowercaseLetters,
      .keyGenerator = keyGeneratorLowercaseLetters },
    { .condition = conditionUppercaseLetters,
      .keyGenerator = keyGeneratorUppercaseLetters },
    { .condition = conditionDigits, .keyGenerator = keyGeneratorDigits },
    { .condition = conditionNumpadDigits,
      .keyGenerator = keyGeneratorNumpadDigits },
};

KeyboardPressEvent KeyboardPressEvent::create(int key, int scancode, int mods)
{
    std::cout << "Creating KeyboardPressEvent with key: " << key
              << " with modifiers: " << mods << std::endl;
    const char *keyName = glfwGetKeyName(key, scancode);
    std::cout << "Name of key: " << (keyName ? keyName : "(null)") << std::endl;
    for (const auto &handler : _handlers)
    {
        if (handler.condition(key, scancode, mods))
        {
            char pressedKey = handler.keyGenerator(key, scancode, mods);
            KeyboardPressEvent event(pressedKey);
            return event;
        }
    }
    // should not go here
    char pressedKey = 0;
    KeyboardPressEvent event(pressedKey);
    return event;
}
