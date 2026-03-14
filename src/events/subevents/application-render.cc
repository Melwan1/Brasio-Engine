#include <events/subevents/application-render.hh>

namespace brasio::events::subevents
{
    ApplicationRenderEvent::ApplicationRenderEvent()
        : categories::ApplicationCategoryEvent<ApplicationRenderEvent>(
              EVENT_APPLICATION_RENDER)
    {}
} // namespace brasio::events::subevents
