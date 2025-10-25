#include <events/subevents/window-move.hh>

WindowMoveEvent::WindowMoveEvent(int downBy, int rightBy)
    : WindowCategoryEvent<WindowMoveEvent>(EVENT_WINDOW_MOVE)
    , _downBy(downBy)
    , _rightBy(rightBy)
{}

int WindowMoveEvent::getUpDisplacement() const
{
    return -getDownDisplacement();
}

int WindowMoveEvent::getDownDisplacement() const
{
    return _downBy;
}

int WindowMoveEvent::getLeftDisplacement() const
{
    return -getRightDisplacement();
}

int WindowMoveEvent::getRightDisplacement() const
{
    return _rightBy;
}
