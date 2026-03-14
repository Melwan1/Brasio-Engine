#include <events/subevents/window-lost-focus.hh>

namespace brasio::events::subevents
{
    WindowLostFocusEvent::WindowLostFocusEvent()
        : WindowCategoryEvent<WindowLostFocusEvent>(EVENT_WINDOW_LOST_FOCUS)
    {}
} // namespace brasio::events::subevents
