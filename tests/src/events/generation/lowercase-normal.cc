#include <gtest/gtest.h>

#include <events/generation/event-key-param.hh> // test file

#include <events/key-generator.hh> // source file

#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::vector<KeyParam> generateLowercaseNormalParams()
{
    std::vector<KeyParam> params;
    char first = 'a';
    char last = 'z';
    for (char c = first; c <= last; c++)
    {
        std::string res(1, c);
        params.emplace_back(GLFW_KEY_A + (c - first), -1, 0, res);
    }
    return params;
}

class Lowercase_Normal : public ::testing::TestWithParam<KeyParam>
{};

TEST_P(Lowercase_Normal, keyGeneration)
{
    const auto &param = GetParam();
    int key = param.key;
    int scancode = param.scancode;
    int mods = param.mods;
    std::string expected = param.expected;
    std::string actual = KeyGenerator::generate(key, scancode, mods);
    EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(Events_KeyGenerator_Generate, Lowercase_Normal,
                         ::testing::ValuesIn(generateLowercaseNormalParams()));
