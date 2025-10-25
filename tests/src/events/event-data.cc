#include <gtest/gtest.h>

#include <events/libevents.hh>

TEST(Events_Event_Data_Keyboard_Press, upperA)
{
    char pressedKey = 'A';
    KeyboardPressEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Press, upperX)
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

TEST(Events_Event_Data_Keyboard_LongPress_PressedKey, upperA)
{
    char pressedKey = 'A';
    unsigned numPresses = 1;
    KeyboardLongPressEvent event(pressedKey, numPresses);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_LongPress_PressedKey, digit3)
{
    char pressedKey = '3';
    unsigned numPresses = 1;
    KeyboardLongPressEvent event(pressedKey, numPresses);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_LongPress_PressedKey, lowerF)
{
    char pressedKey = 'f';
    unsigned numPresses = 1;
    KeyboardLongPressEvent event(pressedKey, numPresses);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_LongPress_PressedKey, plus)
{
    char pressedKey = '+';
    unsigned numPresses = 1;
    KeyboardLongPressEvent event(pressedKey, numPresses);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_LongPress_NumPresses, one)
{
    char pressedKey = 'A';
    unsigned numPresses = 1;
    KeyboardLongPressEvent event(pressedKey, numPresses);
    EXPECT_EQ(event.getNumPresses(), numPresses);
}

TEST(Events_Event_Data_Keyboard_LongPress_NumPresses, zero)
{
    char pressedKey = 'A';
    unsigned numPresses = 0;
    KeyboardLongPressEvent event(pressedKey, numPresses);
    EXPECT_EQ(event.getNumPresses(), numPresses);
}

TEST(Events_Event_Data_Keyboard_LongPress_NumPresses, three)
{
    char pressedKey = 'A';
    unsigned numPresses = 3;
    KeyboardLongPressEvent event(pressedKey, numPresses);
    EXPECT_EQ(event.getNumPresses(), numPresses);
}

TEST(Events_Event_Data_Keyboard_LongPress_NumPresses, oneHundred)
{
    char pressedKey = 'A';
    unsigned numPresses = 100;
    KeyboardLongPressEvent event(pressedKey, numPresses);
    EXPECT_EQ(event.getNumPresses(), numPresses);
}

TEST(Events_Event_Data_Keyboard_Release, upperA)
{
    char pressedKey = 'A';
    KeyboardReleaseEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Release, lowerF)
{
    char pressedKey = 'f';
    KeyboardReleaseEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Release, digit3)
{
    char pressedKey = '3';
    KeyboardReleaseEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Release, plus)
{
    char pressedKey = '+';
    KeyboardReleaseEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Release, sharp)
{
    char pressedKey = '#';
    KeyboardReleaseEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Mouse_Click, left)
{
    enum MouseClickEvent::MouseClickType mouseClickType =
        MouseClickEvent::MOUSE_CLICK_LEFT;
    MouseClickEvent event(mouseClickType);
    EXPECT_EQ(event.getClickType(), mouseClickType);
}

TEST(Events_Event_Data_Mouse_Click, middle)
{
    enum MouseClickEvent::MouseClickType mouseClickType =
        MouseClickEvent::MOUSE_CLICK_MIDDLE;
    MouseClickEvent event(mouseClickType);
    EXPECT_EQ(event.getClickType(), mouseClickType);
}

TEST(Events_Event_Data_Mouse_Click, right)
{
    enum MouseClickEvent::MouseClickType mouseClickType =
        MouseClickEvent::MOUSE_CLICK_RIGHT;
    MouseClickEvent event(mouseClickType);
    EXPECT_EQ(event.getClickType(), mouseClickType);
}
