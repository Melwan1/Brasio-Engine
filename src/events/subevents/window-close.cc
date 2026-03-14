#include <events/subevents/window-close.hh>

namespace brasio::events::subevents
{
    WindowCloseEvent::WindowCloseEvent()
        : WindowCategoryEvent<WindowCloseEvent>(EVENT_WINDOW_CLOSE)
    {}
} // namespace brasio::events::subevents
