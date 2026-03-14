#include <events/subevents/window-focus.hh>

namespace brasio::events::subevents
{
    WindowFocusEvent::WindowFocusEvent()
        : WindowCategoryEvent<WindowFocusEvent>(EVENT_WINDOW_FOCUS)
    {}
} // namespace brasio::events::subevents
