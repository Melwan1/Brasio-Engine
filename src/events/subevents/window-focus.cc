#include <events/subevents/window-focus.hh>

WindowFocusEvent::WindowFocusEvent()
    : WindowCategoryEvent<WindowFocusEvent>(EVENT_WINDOW_FOCUS)
{}
