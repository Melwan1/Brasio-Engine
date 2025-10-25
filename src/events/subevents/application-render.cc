#include <events/subevents/application-render.hh>

ApplicationRenderEvent::ApplicationRenderEvent()
    : ApplicationCategoryEvent<ApplicationRenderEvent>(EVENT_APPLICATION_RENDER)
{}
