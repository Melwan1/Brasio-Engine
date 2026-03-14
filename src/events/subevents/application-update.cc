#include <events/subevents/application-update.hh>

namespace brasio::events::subevents
{
    ApplicationUpdateEvent::ApplicationUpdateEvent()
        : ApplicationCategoryEvent<ApplicationUpdateEvent>(
              EVENT_APPLICATION_UPDATE)
    {}
} // namespace brasio::events::subevents
