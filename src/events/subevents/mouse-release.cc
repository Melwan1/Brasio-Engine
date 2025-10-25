#include <events/subevents/mouse-release.hh>

MouseReleaseEvent::MouseReleaseEvent()
    : MouseCategoryEvent<MouseReleaseEvent>(EVENT_MOUSE_RELEASE)
{}
