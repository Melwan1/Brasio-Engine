#include <events/subevents/mouse-scroll.hh>

namespace brasio::events::subevents
{
    MouseScrollEvent::MouseScrollEvent(
        enum MouseScrollEvent::MouseScrollDirection mouseScrollDirection)
        : MouseCategoryEvent<MouseScrollEvent>(EVENT_MOUSE_SCROLL)
        , _mouseScrollDirection(mouseScrollDirection)
    {}

    enum MouseScrollEvent::MouseScrollDirection
    MouseScrollEvent::getDirection() const
    {
        return _mouseScrollDirection;
    }
} // namespace brasio::events::subevents
