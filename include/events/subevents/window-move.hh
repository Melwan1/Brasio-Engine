#pragma once

#include <events/libevents.hh>

class WindowMoveEvent : public WindowCategoryEvent<WindowMoveEvent>
{
public:
    WindowMoveEvent(int downBy, int rightBy);

    int getDownDisplacement() const;
    int getUpDisplacement() const;
    int getLeftDisplacement() const;
    int getRightDisplacement() const;

private:
    int _downBy;
    int _rightBy;
};
