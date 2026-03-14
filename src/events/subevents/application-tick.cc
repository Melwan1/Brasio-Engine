#include <events/subevents/application-tick.hh>

namespace brasio::events::subevents
{
    ApplicationTickEvent::ApplicationTickEvent()
        : ApplicationCategoryEvent<ApplicationTickEvent>(EVENT_APPLICATION_TICK)
    {}
} // namespace brasio::events::subevents
