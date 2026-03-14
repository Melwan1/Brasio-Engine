#include <gtest/gtest.h>

#include <events/event-validator.hh>

TEST(Events_EventValidator_Valid_Unknown, unknown)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN, brasio::events::EVENT_UNKNOWN));
}

TEST(Events_EventValidator_Valid_Window, close)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_WINDOW_CLOSE));
}

TEST(Events_EventValidator_Valid_Window, resize)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_WINDOW_RESIZE));
}

TEST(Events_EventValidator_Valid_Window, focus)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_WINDOW_FOCUS));
}

TEST(Events_EventValidator_Valid_Window, lostFocus)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_WINDOW_LOST_FOCUS));
}

TEST(Events_EventValidator_Valid_Window, move)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_WINDOW_MOVE));
}

TEST(Events_EventValidator_Valid_Application, tick)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_APPLICATION_TICK));
}

TEST(Events_EventValidator_Valid_Application, update)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_APPLICATION_UPDATE));
}

TEST(Events_EventValidator_Valid_Application, render)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_APPLICATION_RENDER));
}

TEST(Events_EventValidator_Valid_Keyboard, press)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_KEYBOARD_PRESS));
}

TEST(Events_EventValidator_Valid_Keyboard, longPress)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_KEYBOARD_LONG_PRESS));
}

TEST(Events_EventValidator_Valid_Keyboard, release)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_KEYBOARD_RELEASE));
}

TEST(Events_EventValidator_Valid_Mouse, click)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_MOUSE_CLICK));
}

TEST(Events_EventValidator_Valid_Mouse, release)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_MOUSE_RELEASE));
}

TEST(Events_EventValidator_Valid_Mouse, move)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_MOUSE_MOVE));
}

TEST(Events_EventValidator_Valid_Mouse, scroll)
{
    EXPECT_TRUE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_MOUSE_SCROLL));
}

TEST(Events_EventValidator_Invalid_Unknown, window)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW, brasio::events::EVENT_UNKNOWN));
}

TEST(Events_EventValidator_Invalid_Unknown, application)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_UNKNOWN));
}

TEST(Events_EventValidator_Invalid_Unknown, keyboard)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_UNKNOWN));
}

TEST(Events_EventValidator_Invalid_Unknown, mouse)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE, brasio::events::EVENT_UNKNOWN));
}

TEST(Events_EventValidator_Invalid_Window_Close, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_WINDOW_CLOSE));
}

TEST(Events_EventValidator_Invalid_Window_Close, application)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_WINDOW_CLOSE));
}

TEST(Events_EventValidator_Invalid_Window_Close, keyboard)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_WINDOW_CLOSE));
}

TEST(Events_EventValidator_Invalid_Window_Close, mouse)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_WINDOW_CLOSE));
}

TEST(Events_EventValidator_Invalid_Window_Resize, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_WINDOW_RESIZE));
}

TEST(Events_EventValidator_Invalid_Window_Resize, application)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_WINDOW_RESIZE));
}

TEST(Events_EventValidator_Invalid_Window_Resize, keyboard)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_WINDOW_RESIZE));
}

TEST(Events_EventValidator_Invalid_Window_Resize, mouse)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_WINDOW_RESIZE));
}

TEST(Events_EventValidator_Invalid_Window_Focus, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_WINDOW_FOCUS));
}

TEST(Events_EventValidator_Invalid_Window_Focus, application)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_WINDOW_FOCUS));
}

TEST(Events_EventValidator_Invalid_Window_Focus, keyboard)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_WINDOW_FOCUS));
}

TEST(Events_EventValidator_Invalid_Window_Focus, mouse)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_WINDOW_FOCUS));
}

TEST(Events_EventValidator_Invalid_Window_LostFocus, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_WINDOW_LOST_FOCUS));
}

TEST(Events_EventValidator_Invalid_Window_LostFocus, application)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_WINDOW_LOST_FOCUS));
}

TEST(Events_EventValidator_Invalid_Window_LostFocus, keyboard)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_WINDOW_LOST_FOCUS));
}

TEST(Events_EventValidator_Invalid_Window_LostFocus, mouse)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_WINDOW_LOST_FOCUS));
}

TEST(Events_EventValidator_Invalid_Window_Move, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_WINDOW_MOVE));
}

TEST(Events_EventValidator_Invalid_Window_Move, application)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_WINDOW_MOVE));
}

TEST(Events_EventValidator_Invalid_Window_Move, keyboard)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_WINDOW_MOVE));
}

TEST(Events_EventValidator_Invalid_Window_Move, mouse)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_WINDOW_MOVE));
}

TEST(Events_EventValidator_Invalid_Application_Tick, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_APPLICATION_TICK));
}

TEST(Events_EventValidator_Invalid_Application_Tick, window)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_APPLICATION_TICK));
}

TEST(Events_EventValidator_Invalid_Application_Tick, keyboard)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_APPLICATION_TICK));
}

TEST(Events_EventValidator_Invalid_Application_Tick, mouse)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_APPLICATION_TICK));
}

TEST(Events_EventValidator_Invalid_Application_Update, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_APPLICATION_UPDATE));
}

TEST(Events_EventValidator_Invalid_Application_Update, window)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_APPLICATION_UPDATE));
}

TEST(Events_EventValidator_Invalid_Application_Update, keyboard)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_APPLICATION_UPDATE));
}

TEST(Events_EventValidator_Invalid_Application_Update, mouse)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_APPLICATION_UPDATE));
}

TEST(Events_EventValidator_Invalid_Application_Render, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_APPLICATION_RENDER));
}

TEST(Events_EventValidator_Invalid_Application_Render, window)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_APPLICATION_RENDER));
}

TEST(Events_EventValidator_Invalid_Application_Render, keyboard)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_APPLICATION_RENDER));
}

TEST(Events_EventValidator_Invalid_Application_Render, mouse)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_APPLICATION_RENDER));
}

TEST(Events_EventValidator_Invalid_Keyboard_Press, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_KEYBOARD_PRESS));
}

TEST(Events_EventValidator_Invalid_Keyboard_Press, window)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_KEYBOARD_PRESS));
}

TEST(Events_EventValidator_Invalid_Keyboard_Press, application)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_KEYBOARD_PRESS));
}

TEST(Events_EventValidator_Invalid_Keyboard_Press, mouse)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_KEYBOARD_PRESS));
}

TEST(Events_EventValidator_Invalid_Keyboard_LongPress, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_KEYBOARD_LONG_PRESS));
}

TEST(Events_EventValidator_Invalid_Keyboard_LongPress, window)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_KEYBOARD_LONG_PRESS));
}

TEST(Events_EventValidator_Invalid_Keyboard_LongPress, application)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_KEYBOARD_LONG_PRESS));
}

TEST(Events_EventValidator_Invalid_Keyboard_LongPress, mouse)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_KEYBOARD_LONG_PRESS));
}

TEST(Events_EventValidator_Invalid_Keyboard_Release, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_KEYBOARD_RELEASE));
}

TEST(Events_EventValidator_Invalid_Keyboard_Release, window)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_KEYBOARD_RELEASE));
}

TEST(Events_EventValidator_Invalid_Keyboard_Release, application)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_KEYBOARD_RELEASE));
}

TEST(Events_EventValidator_Invalid_Keyboard_Release, mouse)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_MOUSE,
        brasio::events::EVENT_KEYBOARD_RELEASE));
}

TEST(Events_EventValidator_Invalid_Mouse_Click, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_MOUSE_CLICK));
}

TEST(Events_EventValidator_Invalid_Mouse_Click, window)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_MOUSE_CLICK));
}

TEST(Events_EventValidator_Invalid_Mouse_Click, application)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_MOUSE_CLICK));
}

TEST(Events_EventValidator_Invalid_Mouse_Click, keyboard)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_MOUSE_CLICK));
}

TEST(Events_EventValidator_Invalid_Mouse_Release, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_MOUSE_RELEASE));
}

TEST(Events_EventValidator_Invalid_Mouse_Release, window)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_MOUSE_RELEASE));
}

TEST(Events_EventValidator_Invalid_Mouse_Release, application)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_MOUSE_RELEASE));
}

TEST(Events_EventValidator_Invalid_Mouse_Release, keyboard)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_MOUSE_RELEASE));
}

TEST(Events_EventValidator_Invalid_Mouse_Move, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_MOUSE_MOVE));
}

TEST(Events_EventValidator_Invalid_Mouse_Move, window)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_MOUSE_MOVE));
}

TEST(Events_EventValidator_Invalid_Mouse_Move, application)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_MOUSE_MOVE));
}

TEST(Events_EventValidator_Invalid_Mouse_Move, keyboard)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_MOUSE_MOVE));
}

TEST(Events_EventValidator_Invalid_Mouse_Scroll, unknown)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_UNKNOWN,
        brasio::events::EVENT_MOUSE_SCROLL));
}

TEST(Events_EventValidator_Invalid_Mouse_Scroll, window)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_WINDOW,
        brasio::events::EVENT_MOUSE_SCROLL));
}

TEST(Events_EventValidator_Invalid_Mouse_Scroll, application)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_APPLICATION,
        brasio::events::EVENT_MOUSE_SCROLL));
}

TEST(Events_EventValidator_Invalid_Mouse_Scroll, keyboard)
{
    EXPECT_FALSE(brasio::events::EventValidator::validateEventType(
        brasio::events::EVENT_CATEGORY_KEYBOARD,
        brasio::events::EVENT_MOUSE_SCROLL));
}
