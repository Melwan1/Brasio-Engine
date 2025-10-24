#include <events/subevents/window-resize.hh>

WindowResizeEvent::WindowResizeEvent()
    : WindowCategoryEvent<WindowResizeEvent>(EVENT_WINDOW_RESIZE)
{}
