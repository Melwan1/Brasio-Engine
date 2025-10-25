#include <gtest/gtest.h>

#include <events/libevents.hh>
#include "events/subevents/mouse-release.hh"

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

TEST(Events_Event_Data_Mouse_Move_PositionX, borderLeft)
{
    unsigned positionX = 0;
    unsigned positionY = 512;
    MouseMoveEvent event(positionX, positionY);
    EXPECT_EQ(event.getPositionX(), positionX);
}

TEST(Events_Event_Data_Mouse_Move_PositionX, middle)
{
    unsigned positionX = 640;
    unsigned positionY = 512;
    MouseMoveEvent event(positionX, positionY);
    EXPECT_EQ(event.getPositionX(), positionX);
}

TEST(Events_Event_Data_Mouse_Move_PositionX, borderRight)
{
    unsigned positionX = 1919;
    unsigned positionY = 512;
    MouseMoveEvent event(positionX, positionY);
    EXPECT_EQ(event.getPositionX(), positionX);
}

TEST(Events_Event_Data_Mouse_Move_PositionY, borderDown)
{
    unsigned positionX = 512;
    unsigned positionY = 0;
    MouseMoveEvent event(positionX, positionY);
    EXPECT_EQ(event.getPositionY(), positionY);
}

TEST(Events_Event_Data_Mouse_Move_PositionY, middle)
{
    unsigned positionX = 512;
    unsigned positionY = 640;
    MouseMoveEvent event(positionX, positionY);
    EXPECT_EQ(event.getPositionY(), positionY);
}

TEST(Events_Event_Data_Mouse_Move_PositionY, borderUp)
{
    unsigned positionX = 512;
    unsigned positionY = 1079;
    MouseMoveEvent event(positionX, positionY);
    EXPECT_EQ(event.getPositionY(), positionY);
}

TEST(Events_Event_Data_Mouse_Release, left)
{
    enum MouseReleaseEvent::MouseReleaseType mouseReleaseType =
        MouseReleaseEvent::MOUSE_RELEASE_LEFT;
    MouseReleaseEvent event(mouseReleaseType);
    EXPECT_EQ(event.getReleaseType(), mouseReleaseType);
}

TEST(Events_Event_Data_Mouse_Release, middle)
{
    enum MouseReleaseEvent::MouseReleaseType mouseReleaseType =
        MouseReleaseEvent::MOUSE_RELEASE_MIDDLE;
    MouseReleaseEvent event(mouseReleaseType);
    EXPECT_EQ(event.getReleaseType(), mouseReleaseType);
}

TEST(Events_Event_Data_Mouse_Release, right)
{
    enum MouseReleaseEvent::MouseReleaseType mouseReleaseType =
        MouseReleaseEvent::MOUSE_RELEASE_RIGHT;
    MouseReleaseEvent event(mouseReleaseType);
    EXPECT_EQ(event.getReleaseType(), mouseReleaseType);
}
