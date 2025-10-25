#include <events/subevents/mouse-move.hh>

MouseMoveEvent::MouseMoveEvent(unsigned positionX, unsigned positionY)
    : MouseCategoryEvent<MouseMoveEvent>(EVENT_MOUSE_MOVE)
    , _positionX(positionX)
    , _positionY(positionY)
{}

unsigned MouseMoveEvent::getPositionX() const
{
    return _positionX;
}

unsigned MouseMoveEvent::getPositionY() const
{
    return _positionY;
}
