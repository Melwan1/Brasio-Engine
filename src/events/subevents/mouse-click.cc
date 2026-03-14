#include <events/subevents/mouse-click.hh>

namespace brasio::events::subevents
{
    MouseClickEvent::MouseClickEvent(
        enum MouseClickEvent::MouseClickType mouseClickType)
        : MouseCategoryEvent<MouseClickEvent>(EVENT_MOUSE_CLICK)
        , _mouseClickType(mouseClickType)
    {}

    enum MouseClickEvent::MouseClickType MouseClickEvent::getClickType() const
    {
        return _mouseClickType;
    }
} // namespace brasio::events::subevents
