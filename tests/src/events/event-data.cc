#include <gtest/gtest.h>

#include <events/libevents.hh>

TEST(Events_Event_Data_Keyboard_Press, upperA)
{
    const std::string pressedKey = "A";
    brasio::events::subevents::KeyboardPressEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Press, upperX)
{
    const std::string pressedKey = "X";
    brasio::events::subevents::KeyboardPressEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Press, digit3)
{
    const std::string pressedKey = "3";
    brasio::events::subevents::KeyboardPressEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Press, lowerF)
{
    const std::string pressedKey = "f";
    brasio::events::subevents::KeyboardPressEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Press, plus)
{
    const std::string pressedKey = "+";
    brasio::events::subevents::KeyboardPressEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Press, sharp)
{
    const std::string pressedKey = "#";
    brasio::events::subevents::KeyboardPressEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_LongPress_PressedKey, upperA)
{
    const std::string pressedKey = "A";
    unsigned numPresses = 1;
    brasio::events::subevents::KeyboardLongPressEvent event(pressedKey,
                                                            numPresses);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_LongPress_PressedKey, digit3)
{
    const std::string pressedKey = "3";
    unsigned numPresses = 1;
    brasio::events::subevents::KeyboardLongPressEvent event(pressedKey,
                                                            numPresses);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_LongPress_PressedKey, lowerF)
{
    const std::string pressedKey = "f";
    unsigned numPresses = 1;
    brasio::events::subevents::KeyboardLongPressEvent event(pressedKey,
                                                            numPresses);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_LongPress_PressedKey, plus)
{
    const std::string pressedKey = "+";
    unsigned numPresses = 1;
    brasio::events::subevents::KeyboardLongPressEvent event(pressedKey,
                                                            numPresses);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_LongPress_NumPresses, one)
{
    const std::string pressedKey = "A";
    unsigned numPresses = 1;
    brasio::events::subevents::KeyboardLongPressEvent event(pressedKey,
                                                            numPresses);
    EXPECT_EQ(event.getNumPresses(), numPresses);
}

TEST(Events_Event_Data_Keyboard_LongPress_NumPresses, zero)
{
    const std::string pressedKey = "A";
    unsigned numPresses = 0;
    brasio::events::subevents::KeyboardLongPressEvent event(pressedKey,
                                                            numPresses);
    EXPECT_EQ(event.getNumPresses(), numPresses);
}

TEST(Events_Event_Data_Keyboard_LongPress_NumPresses, three)
{
    const std::string pressedKey = "A";
    unsigned numPresses = 3;
    brasio::events::subevents::KeyboardLongPressEvent event(pressedKey,
                                                            numPresses);
    EXPECT_EQ(event.getNumPresses(), numPresses);
}

TEST(Events_Event_Data_Keyboard_LongPress_NumPresses, oneHundred)
{
    const std::string pressedKey = "A";
    unsigned numPresses = 100;
    brasio::events::subevents::KeyboardLongPressEvent event(pressedKey,
                                                            numPresses);
    EXPECT_EQ(event.getNumPresses(), numPresses);
}

TEST(Events_Event_Data_Keyboard_Release, upperA)
{
    const std::string pressedKey = "A";
    brasio::events::subevents::KeyboardReleaseEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Release, lowerF)
{
    const std::string pressedKey = "f";
    brasio::events::subevents::KeyboardReleaseEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Release, digit3)
{
    const std::string pressedKey = "3";
    brasio::events::subevents::KeyboardReleaseEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Release, plus)
{
    const std::string pressedKey = "+";
    brasio::events::subevents::KeyboardReleaseEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Keyboard_Release, sharp)
{
    const std::string pressedKey = "#";
    brasio::events::subevents::KeyboardReleaseEvent event(pressedKey);
    EXPECT_EQ(event.getPressedKey(), pressedKey);
}

TEST(Events_Event_Data_Mouse_Click, left)
{
    enum brasio::events::subevents::MouseClickEvent::MouseClickType
        mouseClickType =
            brasio::events::subevents::MouseClickEvent::MOUSE_CLICK_LEFT;
    brasio::events::subevents::MouseClickEvent event(mouseClickType);
    EXPECT_EQ(event.getClickType(), mouseClickType);
}

TEST(Events_Event_Data_Mouse_Click, middle)
{
    enum brasio::events::subevents::MouseClickEvent::MouseClickType
        mouseClickType =
            brasio::events::subevents::MouseClickEvent::MOUSE_CLICK_MIDDLE;
    brasio::events::subevents::MouseClickEvent event(mouseClickType);
    EXPECT_EQ(event.getClickType(), mouseClickType);
}

TEST(Events_Event_Data_Mouse_Click, right)
{
    enum brasio::events::subevents::MouseClickEvent::MouseClickType
        mouseClickType =
            brasio::events::subevents::MouseClickEvent::MOUSE_CLICK_RIGHT;
    brasio::events::subevents::MouseClickEvent event(mouseClickType);
    EXPECT_EQ(event.getClickType(), mouseClickType);
}

TEST(Events_Event_Data_Mouse_Move_PositionX, borderLeft)
{
    unsigned positionX = 0;
    unsigned positionY = 512;
    brasio::events::subevents::MouseMoveEvent event(positionX, positionY);
    EXPECT_EQ(event.getPositionX(), positionX);
}

TEST(Events_Event_Data_Mouse_Move_PositionX, middle)
{
    unsigned positionX = 640;
    unsigned positionY = 512;
    brasio::events::subevents::MouseMoveEvent event(positionX, positionY);
    EXPECT_EQ(event.getPositionX(), positionX);
}

TEST(Events_Event_Data_Mouse_Move_PositionX, borderRight)
{
    unsigned positionX = 1919;
    unsigned positionY = 512;
    brasio::events::subevents::MouseMoveEvent event(positionX, positionY);
    EXPECT_EQ(event.getPositionX(), positionX);
}

TEST(Events_Event_Data_Mouse_Move_PositionY, borderDown)
{
    unsigned positionX = 512;
    unsigned positionY = 0;
    brasio::events::subevents::MouseMoveEvent event(positionX, positionY);
    EXPECT_EQ(event.getPositionY(), positionY);
}

TEST(Events_Event_Data_Mouse_Move_PositionY, middle)
{
    unsigned positionX = 512;
    unsigned positionY = 640;
    brasio::events::subevents::MouseMoveEvent event(positionX, positionY);
    EXPECT_EQ(event.getPositionY(), positionY);
}

TEST(Events_Event_Data_Mouse_Move_PositionY, borderUp)
{
    unsigned positionX = 512;
    unsigned positionY = 1079;
    brasio::events::subevents::MouseMoveEvent event(positionX, positionY);
    EXPECT_EQ(event.getPositionY(), positionY);
}

TEST(Events_Event_Data_Mouse_Release, left)
{
    enum brasio::events::subevents::MouseReleaseEvent::MouseReleaseType
        mouseReleaseType =
            brasio::events::subevents::MouseReleaseEvent::MOUSE_RELEASE_LEFT;
    brasio::events::subevents::MouseReleaseEvent event(mouseReleaseType);
    EXPECT_EQ(event.getReleaseType(), mouseReleaseType);
}

TEST(Events_Event_Data_Mouse_Release, middle)
{
    enum brasio::events::subevents::MouseReleaseEvent::MouseReleaseType
        mouseReleaseType =
            brasio::events::subevents::MouseReleaseEvent::MOUSE_RELEASE_MIDDLE;
    brasio::events::subevents::MouseReleaseEvent event(mouseReleaseType);
    EXPECT_EQ(event.getReleaseType(), mouseReleaseType);
}

TEST(Events_Event_Data_Mouse_Release, right)
{
    enum brasio::events::subevents::MouseReleaseEvent::MouseReleaseType
        mouseReleaseType =
            brasio::events::subevents::MouseReleaseEvent::MOUSE_RELEASE_RIGHT;
    brasio::events::subevents::MouseReleaseEvent event(mouseReleaseType);
    EXPECT_EQ(event.getReleaseType(), mouseReleaseType);
}

TEST(Events_Event_Data_Mouse_Scroll, up)
{
    enum brasio::events::subevents::MouseScrollEvent::MouseScrollDirection
        mouseScrollDirection =
            brasio::events::subevents::MouseScrollEvent::MOUSE_SCROLL_UP;
    brasio::events::subevents::MouseScrollEvent event(mouseScrollDirection);
    EXPECT_EQ(event.getDirection(), mouseScrollDirection);
}

TEST(Events_Event_Data_Mouse_Scroll, down)
{
    enum brasio::events::subevents::MouseScrollEvent::MouseScrollDirection
        mouseScrollDirection =
            brasio::events::subevents::MouseScrollEvent::MOUSE_SCROLL_DOWN;
    brasio::events::subevents::MouseScrollEvent event(mouseScrollDirection);
    EXPECT_EQ(event.getDirection(), mouseScrollDirection);
}

TEST(Events_Event_Data_Window_Move_DownDisplacement, up50)
{
    int downBy = -50;
    int rightBy = 0;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getDownDisplacement(), downBy);
}

TEST(Events_Event_Data_Window_Move_DownDisplacement, up2right1)
{
    int downBy = -2;
    int rightBy = 1;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getDownDisplacement(), downBy);
}

TEST(Events_Event_Data_Window_Move_DownDisplacement, right16)
{
    int downBy = 10;
    int rightBy = 15;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getDownDisplacement(), downBy);
}

TEST(Events_Event_Data_Window_Move_DownDisplacement, down10right15)
{
    int downBy = 10;
    int rightBy = 15;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getDownDisplacement(), downBy);
}

TEST(Events_Event_Data_Window_Move_DownDisplacement, down20)
{
    int downBy = 20;
    int rightBy = 0;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getDownDisplacement(), downBy);
}

TEST(Events_Event_Data_Window_Move_DownDisplacement, down5left17)
{
    int downBy = 5;
    int rightBy = -17;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getDownDisplacement(), downBy);
}

TEST(Events_Event_Data_Window_Move_DownDisplacement, left32)
{
    int downBy = 0;
    int rightBy = -32;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getDownDisplacement(), downBy);
}

TEST(Events_Event_Data_Window_Move_DownDisplacement, up7left8)
{
    int downBy = -7;
    int rightBy = -8;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getDownDisplacement(), downBy);
}

TEST(Events_Event_Data_Window_Move_UpDisplacement, up50)
{
    int downBy = -50;
    int rightBy = 0;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getUpDisplacement(), -downBy);
}

TEST(Events_Event_Data_Window_Move_UpDisplacement, up2right1)
{
    int downBy = -2;
    int rightBy = 1;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getUpDisplacement(), -downBy);
}

TEST(Events_Event_Data_Window_Move_UpDisplacement, right16)
{
    int downBy = 10;
    int rightBy = 15;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getUpDisplacement(), -downBy);
}

TEST(Events_Event_Data_Window_Move_UpDisplacement, down10right15)
{
    int downBy = 10;
    int rightBy = 15;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getUpDisplacement(), -downBy);
}

TEST(Events_Event_Data_Window_Move_UpDisplacement, down20)
{
    int downBy = 20;
    int rightBy = 0;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getUpDisplacement(), -downBy);
}

TEST(Events_Event_Data_Window_Move_UpDisplacement, down5left17)
{
    int downBy = 5;
    int rightBy = -17;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getUpDisplacement(), -downBy);
}

TEST(Events_Event_Data_Window_Move_UpDisplacement, left32)
{
    int downBy = 0;
    int rightBy = -32;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getUpDisplacement(), -downBy);
}

TEST(Events_Event_Data_Window_Move_UpDisplacement, up7left8)
{
    int downBy = -7;
    int rightBy = -8;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getUpDisplacement(), -downBy);
}

TEST(Events_Event_Data_Window_Move_LeftDisplacement, up50)
{
    int downBy = -50;
    int rightBy = 0;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getLeftDisplacement(), -rightBy);
}

TEST(Events_Event_Data_Window_Move_LeftDisplacement, up2right1)
{
    int downBy = -2;
    int rightBy = 1;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getLeftDisplacement(), -rightBy);
}

TEST(Events_Event_Data_Window_Move_LeftDisplacement, right16)
{
    int downBy = 10;
    int rightBy = 15;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getLeftDisplacement(), -rightBy);
}

TEST(Events_Event_Data_Window_Move_LeftDisplacement, down10right15)
{
    int downBy = 10;
    int rightBy = 15;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getLeftDisplacement(), -rightBy);
}

TEST(Events_Event_Data_Window_Move_LeftDisplacement, down20)
{
    int downBy = 20;
    int rightBy = 0;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getLeftDisplacement(), -rightBy);
}

TEST(Events_Event_Data_Window_Move_LeftDisplacement, down5left17)
{
    int downBy = 5;
    int rightBy = -17;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getLeftDisplacement(), -rightBy);
}

TEST(Events_Event_Data_Window_Move_LeftDisplacement, left32)
{
    int downBy = 0;
    int rightBy = -32;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getLeftDisplacement(), -rightBy);
}

TEST(Events_Event_Data_Window_Move_LeftDisplacement, up7left8)
{
    int downBy = -7;
    int rightBy = -8;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getLeftDisplacement(), -rightBy);
}

TEST(Events_Event_Data_Window_Move_RightDisplacement, up50)
{
    int downBy = -50;
    int rightBy = 0;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getRightDisplacement(), rightBy);
}

TEST(Events_Event_Data_Window_Move_RightDisplacement, up2right1)
{
    int downBy = -2;
    int rightBy = 1;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getRightDisplacement(), rightBy);
}

TEST(Events_Event_Data_Window_Move_RightDisplacement, right16)
{
    int downBy = 10;
    int rightBy = 15;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getRightDisplacement(), rightBy);
}

TEST(Events_Event_Data_Window_Move_RightDisplacement, down10right15)
{
    int downBy = 10;
    int rightBy = 15;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getRightDisplacement(), rightBy);
}

TEST(Events_Event_Data_Window_Move_RightDisplacement, down20)
{
    int downBy = 20;
    int rightBy = 0;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getRightDisplacement(), rightBy);
}

TEST(Events_Event_Data_Window_Move_RightDisplacement, down5left17)
{
    int downBy = 5;
    int rightBy = -17;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getRightDisplacement(), rightBy);
}

TEST(Events_Event_Data_Window_Move_RightDisplacement, left32)
{
    int downBy = 0;
    int rightBy = -32;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getRightDisplacement(), rightBy);
}

TEST(Events_Event_Data_Window_Move_RightDisplacement, up7left8)
{
    int downBy = -7;
    int rightBy = -8;
    brasio::events::subevents::WindowMoveEvent event(downBy, rightBy);
    EXPECT_EQ(event.getRightDisplacement(), rightBy);
}

TEST(Events_Event_Data_Window_Resize_ToggleFullscreen, toggle)
{
    bool toggleFullScreen = true;
    unsigned sizeX = 0;
    unsigned sizeY = 0;
    brasio::events::subevents::WindowResizeEvent event(toggleFullScreen, sizeX,
                                                       sizeY);
    EXPECT_EQ(event.getToggleFullscreen(), toggleFullScreen);
}

TEST(Events_Event_Data_Window_Resize_ToggleFullscreen, noToggle)
{
    bool toggleFullScreen = false;
    unsigned sizeX = 0;
    unsigned sizeY = 0;
    brasio::events::subevents::WindowResizeEvent event(toggleFullScreen, sizeX,
                                                       sizeY);
    EXPECT_EQ(event.getToggleFullscreen(), toggleFullScreen);
}

TEST(Events_Event_Data_Window_Resize_SizeX, zero)
{
    bool toggleFullScreen = false;
    unsigned sizeX = 0;
    unsigned sizeY = 0;
    brasio::events::subevents::WindowResizeEvent event(toggleFullScreen, sizeX,
                                                       sizeY);
    EXPECT_EQ(event.getSizeX(), sizeX);
}

TEST(Events_Event_Data_Window_Resize_SizeX, classic)
{
    bool toggleFullScreen = false;
    unsigned sizeX = 1920;
    unsigned sizeY = 1080;
    brasio::events::subevents::WindowResizeEvent event(toggleFullScreen, sizeX,
                                                       sizeY);
    EXPECT_EQ(event.getSizeX(), sizeX);
}

TEST(Events_Event_Data_Window_Resize_SizeX, reduce)
{
    bool toggleFullScreen = false;
    unsigned sizeX = 640;
    unsigned sizeY = 480;
    brasio::events::subevents::WindowResizeEvent event(toggleFullScreen, sizeX,
                                                       sizeY);
    EXPECT_EQ(event.getSizeX(), sizeX);
}

TEST(Events_Event_Data_Window_Resize_SizeY, zero)
{
    bool toggleFullScreen = false;
    unsigned sizeX = 0;
    unsigned sizeY = 0;
    brasio::events::subevents::WindowResizeEvent event(toggleFullScreen, sizeX,
                                                       sizeY);
    EXPECT_EQ(event.getSizeY(), sizeY);
}

TEST(Events_Event_Data_Window_Resize_SizeY, classic)
{
    bool toggleFullScreen = false;
    unsigned sizeX = 1920;
    unsigned sizeY = 1080;
    brasio::events::subevents::WindowResizeEvent event(toggleFullScreen, sizeX,
                                                       sizeY);
    EXPECT_EQ(event.getSizeY(), sizeY);
}

TEST(Events_Event_Data_Window_Resize_SizeY, reduce)
{
    bool toggleFullScreen = false;
    unsigned sizeX = 640;
    unsigned sizeY = 480;
    brasio::events::subevents::WindowResizeEvent event(toggleFullScreen, sizeX,
                                                       sizeY);
    EXPECT_EQ(event.getSizeY(), sizeY);
}
