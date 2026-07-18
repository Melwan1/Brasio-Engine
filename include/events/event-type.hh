#pragma once

namespace brasio::events
{

    enum EventType
    {
        EVENT_UNKNOWN = 0,
        EVENT_WINDOW_CLOSE, // = 1
        EVENT_WINDOW_RESIZE, // = 2
        EVENT_WINDOW_FOCUS, // = 3
        EVENT_WINDOW_LOST_FOCUS, // = 4
        EVENT_WINDOW_MOVE, // = 5
        EVENT_APPLICATION_TICK, // = 6
        EVENT_APPLICATION_UPDATE, // = 7
        EVENT_APPLICATION_RENDER, // = 8
        EVENT_KEYBOARD_PRESS, // = 9
        EVENT_KEYBOARD_LONG_PRESS, // = 10
        EVENT_KEYBOARD_RELEASE, // = 11
        EVENT_MOUSE_CLICK, // = 12
        EVENT_MOUSE_RELEASE, // = 13
        EVENT_MOUSE_MOVE, // = 14
        EVENT_MOUSE_SCROLL, // = 15
    };
}
