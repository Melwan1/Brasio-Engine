#include <events/subevents/application-tick.hh>

ApplicationTickEvent::ApplicationTickEvent()
    : ApplicationCategoryEvent<ApplicationTickEvent>(EVENT_APPLICATION_TICK)
{}
