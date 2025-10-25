#include <events/categories/categories.hh>
#include <events/subevents/subevents.hh>

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
