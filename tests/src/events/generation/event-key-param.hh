#pragma once

#include <string>

struct KeyParam
{
    int key;
    int scancode;
    int mods;
    std::string expected;
};
