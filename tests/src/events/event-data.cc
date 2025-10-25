#include <gtest/gtest.h>

#include <events/libevents.hh>

TEST(Events_Event_Data_Keyboard_Press, upperA)
{
    char pressedKey = 'A';
    KeyboardPressEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Press, pperX)
{
    char pressedKey = 'X';
    KeyboardPressEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Press, digit3)
{
    char pressedKey = '3';
    KeyboardPressEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Press, lowerF)
{
    char pressedKey = 'f';
    KeyboardPressEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Press, plus)
{
    char pressedKey = '+';
    KeyboardPressEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Press, sharp)
{
    char pressedKey = '#';
    KeyboardPressEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}
