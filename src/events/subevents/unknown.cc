#include <events/subevents/unknown.hh>

UnknownEvent::UnknownEvent()
    : UnknownCategoryEvent<UnknownEvent>(EVENT_UNKNOWN)
{}
