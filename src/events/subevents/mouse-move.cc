#include <events/subevents/mouse-click.hh>

MouseClickEvent::MouseClickEvent()
    : MouseCategoryEvent<MouseClickEvent>(EVENT_MOUSE_CLICK)
{}
