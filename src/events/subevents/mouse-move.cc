#include <events/subevents/mouse-move.hh>

MouseMoveEvent::MouseMoveEvent()
    : MouseCategoryEvent<MouseMoveEvent>(EVENT_MOUSE_MOVE)
{}
