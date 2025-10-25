#include <events/subevents/mouse-release.hh>

MouseReleaseEvent::MouseReleaseEvent(
    enum MouseReleaseEvent::MouseReleaseType mouseReleaseType)
    : MouseCategoryEvent<MouseReleaseEvent>(EVENT_MOUSE_RELEASE)
    , _mouseReleaseType(mouseReleaseType)
{}

enum MouseReleaseEvent::MouseReleaseType
MouseReleaseEvent::getReleaseType() const
{
    return _mouseReleaseType;
}
