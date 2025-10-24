#include <events/subevents/mouse-scroll.hh>

MouseScrollEvent::MouseScrollEvent()
    : MouseCategoryEvent<MouseScrollEvent>(EVENT_MOUSE_SCROLL)
{}
