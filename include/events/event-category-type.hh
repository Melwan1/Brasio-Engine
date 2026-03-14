#pragma once

namespace brasio::events
{

    enum EventCategoryType
    {
        EVENT_CATEGORY_WINDOW = 0b0001, // 1
        EVENT_CATEGORY_APPLICATION = 0b0010, // 2
        EVENT_CATEGORY_KEYBOARD = 0b0100, // 4
        EVENT_CATEGORY_MOUSE = 0b1000, // 8
        EVENT_CATEGORY_UNKNOWN = 0b0000, // 0
    };
}
