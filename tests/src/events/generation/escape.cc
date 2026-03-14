#include <gtest/gtest.h>

#include <events/generation/event-key-param.hh>

#include <events/key-generator.hh>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

TEST(Events_KeyGenerator_Generate_Escape, escape)
{
    int key = GLFW_KEY_ESCAPE;
    int scancode = -1;
    int mods = 0;
    std::string expected = "ESC";
    std::string actual =
        brasio::events::KeyGenerator::generate(key, scancode, mods);
    EXPECT_EQ(expected, actual);
}
