#pragma once

#include <events/libevents.hh>

class KeyboardLongPressEvent
    : public KeyboardCategoryEvent<KeyboardLongPressEvent>
{
public:
    KeyboardLongPressEvent();
};
