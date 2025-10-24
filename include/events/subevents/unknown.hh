#pragma once

#include <events/libevents.hh>

class UnknownEvent : public UnknownCategoryEvent<UnknownEvent>
{
public:
    UnknownEvent();
};
