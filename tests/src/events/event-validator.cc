#include <gtest/gtest.h>

#include <events/event-validator.hh>

TEST(Events_EventValidator_Valid_Unknown, eventUnknown)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                  EVENT_UNKNOWN));
}

TEST(Events_EventValidator_Valid_Window, eventWindowClose)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                  EVENT_WINDOW_CLOSE));
}

TEST(Events_EventValidator_Valid_Window, eventWindowResize)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                  EVENT_WINDOW_RESIZE));
}

TEST(Events_EventValidator_Valid_Window, eventWindowFocus)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                  EVENT_WINDOW_FOCUS));
}

TEST(Events_EventValidator_Valid_Window, eventWindowLostFocus)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                  EVENT_WINDOW_LOST_FOCUS));
}

TEST(Events_EventValidator_Valid_Window, eventWindowMove)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                  EVENT_WINDOW_MOVE));
}

TEST(Events_EventValidator_Valid_Application, eventApplicationTick)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                  EVENT_APPLICATION_TICK));
}

TEST(Events_EventValidator_Valid_Application, eventApplicationUpdate)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                  EVENT_APPLICATION_UPDATE));
}

TEST(Events_EventValidator_Valid_Application, eventApplicationRender)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                  EVENT_APPLICATION_RENDER));
}

TEST(Events_EventValidator_Valid_Keyboard, eventKeyboardPress)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                  EVENT_KEYBOARD_PRESS));
}

TEST(Events_EventValidator_Valid_Keyboard, eventKeyboardLongPress)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                  EVENT_KEYBOARD_LONG_PRESS));
}

TEST(Events_EventValidator_Valid_Keyboard, eventKeyboardRelease)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                  EVENT_KEYBOARD_RELEASE));
}

TEST(Events_EventValidator_Valid_Mouse, eventMouseClick)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                  EVENT_MOUSE_CLICK));
}

TEST(Events_EventValidator_Valid_Mouse, eventMouseRelease)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                  EVENT_MOUSE_RELEASE));
}

TEST(Events_EventValidator_Valid_Mouse, eventMouseMove)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                  EVENT_MOUSE_MOVE));
}

TEST(Events_EventValidator_Valid_Mouse, eventMouseScroll)
{
    EXPECT_TRUE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                  EVENT_MOUSE_SCROLL));
}

TEST(Events_EventValidator_Invalid_Unknown, eventCategoryWindow)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                   EVENT_UNKNOWN));
}

TEST(Events_EventValidator_Invalid_Unknown, eventCategoryApplication)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                   EVENT_UNKNOWN));
}

TEST(Events_EventValidator_Invalid_Unknown, eventCategoryKeyboard)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                   EVENT_UNKNOWN));
}

TEST(Events_EventValidator_Invalid_Unknown, eventCategoryMouse)
{
    EXPECT_FALSE(
        EventValidator::validateEventType(EVENT_CATEGORY_MOUSE, EVENT_UNKNOWN));
}

TEST(Events_EventValidator_Invalid_WindowClose, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_WINDOW_CLOSE));
}

TEST(Events_EventValidator_Invalid_WindowClose, eventCategoryApplication)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                   EVENT_WINDOW_CLOSE));
}

TEST(Events_EventValidator_Invalid_WindowClose, eventCategoryKeyboard)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                   EVENT_WINDOW_CLOSE));
}

TEST(Events_EventValidator_Invalid_WindowClose, eventCategoryMouse)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                   EVENT_WINDOW_CLOSE));
}

TEST(Events_EventValidator_Invalid_WindowResize, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_WINDOW_RESIZE));
}

TEST(Events_EventValidator_Invalid_WindowResize, eventCategoryApplication)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                   EVENT_WINDOW_RESIZE));
}

TEST(Events_EventValidator_Invalid_WindowResize, eventCategoryKeyboard)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                   EVENT_WINDOW_RESIZE));
}

TEST(Events_EventValidator_Invalid_WindowResize, eventCategoryMouse)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                   EVENT_WINDOW_RESIZE));
}

TEST(Events_EventValidator_Invalid_WindowFocus, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_WINDOW_FOCUS));
}

TEST(Events_EventValidator_Invalid_WindowFocus, eventCategoryApplication)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                   EVENT_WINDOW_FOCUS));
}

TEST(Events_EventValidator_Invalid_WindowFocus, eventCategoryKeyboard)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                   EVENT_WINDOW_FOCUS));
}

TEST(Events_EventValidator_Invalid_WindowFocus, eventCategoryMouse)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                   EVENT_WINDOW_FOCUS));
}

TEST(Events_EventValidator_Invalid_WindowLostFocus, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_WINDOW_LOST_FOCUS));
}

TEST(Events_EventValidator_Invalid_WindowLostFocus, eventCategoryApplication)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                   EVENT_WINDOW_LOST_FOCUS));
}

TEST(Events_EventValidator_Invalid_WindowLostFocus, eventCategoryKeyboard)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                   EVENT_WINDOW_LOST_FOCUS));
}

TEST(Events_EventValidator_Invalid_WindowLostFocus, eventCategoryMouse)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                   EVENT_WINDOW_LOST_FOCUS));
}

TEST(Events_EventValidator_Invalid_WindowMove, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_WINDOW_MOVE));
}

TEST(Events_EventValidator_Invalid_WindowMove, eventCategoryApplication)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                   EVENT_WINDOW_MOVE));
}

TEST(Events_EventValidator_Invalid_WindowMove, eventCategoryKeyboard)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                   EVENT_WINDOW_MOVE));
}

TEST(Events_EventValidator_Invalid_WindowMove, eventCategoryMouse)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                   EVENT_WINDOW_MOVE));
}

TEST(Events_EventValidator_Invalid_ApplicationTick, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_APPLICATION_TICK));
}

TEST(Events_EventValidator_Invalid_ApplicationTick, eventCategoryWindow)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                   EVENT_APPLICATION_TICK));
}

TEST(Events_EventValidator_Invalid_ApplicationTick, eventCategoryKeyboard)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                   EVENT_APPLICATION_TICK));
}

TEST(Events_EventValidator_Invalid_ApplicationTick, eventCategoryMouse)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                   EVENT_APPLICATION_TICK));
}

TEST(Events_EventValidator_Invalid_ApplicationUpdate, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_APPLICATION_UPDATE));
}

TEST(Events_EventValidator_Invalid_ApplicationUpdate, eventCategoryWindow)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                   EVENT_APPLICATION_UPDATE));
}

TEST(Events_EventValidator_Invalid_ApplicationUpdate, eventCategoryKeyboard)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                   EVENT_APPLICATION_UPDATE));
}

TEST(Events_EventValidator_Invalid_ApplicationUpdate, eventCategoryMouse)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                   EVENT_APPLICATION_UPDATE));
}

TEST(Events_EventValidator_Invalid_ApplicationRender, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_APPLICATION_RENDER));
}

TEST(Events_EventValidator_Invalid_ApplicationRender, eventCategoryWindow)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                   EVENT_APPLICATION_RENDER));
}

TEST(Events_EventValidator_Invalid_ApplicationRender, eventCategoryKeyboard)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                   EVENT_APPLICATION_RENDER));
}

TEST(Events_EventValidator_Invalid_ApplicationRender, eventCategoryMouse)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                   EVENT_APPLICATION_RENDER));
}

TEST(Events_EventValidator_Invalid_KeyboardPress, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_KEYBOARD_PRESS));
}

TEST(Events_EventValidator_Invalid_KeyboardPress, eventCategoryWindow)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                   EVENT_KEYBOARD_PRESS));
}

TEST(Events_EventValidator_Invalid_KeyboardPress, eventCategoryApplication)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                   EVENT_KEYBOARD_PRESS));
}

TEST(Events_EventValidator_Invalid_KeyboardPress, eventCategoryMouse)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                   EVENT_KEYBOARD_PRESS));
}

TEST(Events_EventValidator_Invalid_KeyboardLongPress, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_KEYBOARD_LONG_PRESS));
}

TEST(Events_EventValidator_Invalid_KeyboardLongPress, eventCategoryWindow)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                   EVENT_KEYBOARD_LONG_PRESS));
}

TEST(Events_EventValidator_Invalid_KeyboardLongPress, eventCategoryApplication)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                   EVENT_KEYBOARD_LONG_PRESS));
}

TEST(Events_EventValidator_Invalid_KeyboardLongPress, eventCategoryMouse)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                   EVENT_KEYBOARD_LONG_PRESS));
}

TEST(Events_EventValidator_Invalid_KeyboardRelease, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_KEYBOARD_RELEASE));
}

TEST(Events_EventValidator_Invalid_KeyboardRelease, eventCategoryWindow)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                   EVENT_KEYBOARD_RELEASE));
}

TEST(Events_EventValidator_Invalid_KeyboardRelease, eventCategoryApplication)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                   EVENT_KEYBOARD_RELEASE));
}

TEST(Events_EventValidator_Invalid_KeyboardRelease, eventCategoryMouse)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_MOUSE,
                                                   EVENT_KEYBOARD_RELEASE));
}

TEST(Events_EventValidator_Invalid_MouseClick, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_MOUSE_CLICK));
}

TEST(Events_EventValidator_Invalid_MouseClick, eventCategoryWindow)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                   EVENT_MOUSE_CLICK));
}

TEST(Events_EventValidator_Invalid_MouseClick, eventCategoryApplication)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                   EVENT_MOUSE_CLICK));
}

TEST(Events_EventValidator_Invalid_MouseClick, eventCategoryKeyboard)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                   EVENT_MOUSE_CLICK));
}

TEST(Events_EventValidator_Invalid_MouseRelease, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_MOUSE_RELEASE));
}

TEST(Events_EventValidator_Invalid_MouseRelease, eventCategoryWindow)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                   EVENT_MOUSE_RELEASE));
}

TEST(Events_EventValidator_Invalid_MouseRelease, eventCategoryApplication)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                   EVENT_MOUSE_RELEASE));
}

TEST(Events_EventValidator_Invalid_MouseRelease, eventCategoryKeyboard)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                   EVENT_MOUSE_RELEASE));
}

TEST(Events_EventValidator_Invalid_MouseMove, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_MOUSE_MOVE));
}

TEST(Events_EventValidator_Invalid_MouseMove, eventCategoryWindow)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                   EVENT_MOUSE_MOVE));
}

TEST(Events_EventValidator_Invalid_MouseMove, eventCategoryApplication)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                   EVENT_MOUSE_MOVE));
}

TEST(Events_EventValidator_Invalid_MouseMove, eventCategoryKeyboard)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                   EVENT_MOUSE_MOVE));
}

TEST(Events_EventValidator_Invalid_MouseScroll, eventCategoryUnknown)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_UNKNOWN,
                                                   EVENT_MOUSE_SCROLL));
}

TEST(Events_EventValidator_Invalid_MouseScroll, eventCategoryWindow)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_WINDOW,
                                                   EVENT_MOUSE_SCROLL));
}

TEST(Events_EventValidator_Invalid_MouseScroll, eventCategoryApplication)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_APPLICATION,
                                                   EVENT_MOUSE_SCROLL));
}

TEST(Events_EventValidator_Invalid_MouseScroll, eventCategoryKeyboard)
{
    EXPECT_FALSE(EventValidator::validateEventType(EVENT_CATEGORY_KEYBOARD,
                                                   EVENT_MOUSE_SCROLL));
}
