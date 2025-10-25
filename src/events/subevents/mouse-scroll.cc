#include <events/subevents/mouse-scroll.hh>

MouseScrollEvent::MouseScrollEvent(
    enum MouseScrollEvent::MouseScrollDirection mouseScrollDirection)
    : MouseCategoryEvent<MouseScrollEvent>(EVENT_MOUSE_SCROLL)
    , _mouseScrollDirection(mouseScrollDirection)
{}

enum MouseScrollEvent::MouseScrollDirection
MouseScrollEvent::getDirection() const
{
    return _mouseScrollDirection;
}
