#include <gtest/gtest.h>

#include <events/generation/event-key-param.hh> // test file

#include <events/key-generator.hh> // source file

#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::vector<KeyParam> generateDigitClassicParams()
{
    std::vector<KeyParam> params;
    char first = '0';
    char last = '9';
    for (char c = first; c <= last; c++)
    {
        std::string res(1, c);
        params.emplace_back(GLFW_KEY_0 + (c - first), -1, GLFW_MOD_SHIFT, res);
    }
    return params;
}

class Digit_Classic : public ::testing::TestWithParam<KeyParam>
{};

TEST_P(Digit_Classic, keyGeneration)
{
    const auto &param = GetParam();
    int key = param.key;
    int scancode = param.scancode;
    int mods = param.mods;
    std::string expected = param.expected;
    std::string actual = KeyGenerator::generate(key, scancode, mods);
    EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(Events_KeyGenerator_Generate, Digit_Classic,
                         ::testing::ValuesIn(generateDigitClassicParams()));
