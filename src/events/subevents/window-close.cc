#include <events/subevents/window-close.hh>

WindowCloseEvent::WindowCloseEvent()
    : WindowCategoryEvent<WindowCloseEvent>(EVENT_WINDOW_CLOSE)
{}
