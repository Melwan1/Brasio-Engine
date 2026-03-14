#include <events/subevents/unknown.hh>

namespace brasio::events::subevents
{
    UnknownEvent::UnknownEvent()
        : UnknownCategoryEvent<UnknownEvent>(EVENT_UNKNOWN)
    {}
} // namespace brasio::events::subevents
