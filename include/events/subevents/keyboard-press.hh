#pragma once

#include <events/libevents.hh>

class KeyboardPressEvent : public KeyboardCategoryEvent<KeyboardPressEvent>
{
public:
    KeyboardPressEvent();
};
