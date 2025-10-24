#include <events/subevents/window-lost-focus.hh>

WindowLostFocusEvent::WindowLostFocusEvent()
    : WindowCategoryEvent<WindowLostFocusEvent>(EVENT_WINDOW_LOST_FOCUS)
{}
