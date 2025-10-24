#include <events/subevents/window-move.hh>

WindowMoveEvent::WindowMoveEvent()
    : WindowCategoryEvent<WindowMoveEvent>(EVENT_WINDOW_MOVE)
{}
