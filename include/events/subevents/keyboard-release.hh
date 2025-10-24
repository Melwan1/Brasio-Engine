#pragma once

#include <events/libevents.hh>

class KeyboardReleaseEvent : public KeyboardCategoryEvent<KeyboardReleaseEvent>
{
public:
    KeyboardReleaseEvent();
};
