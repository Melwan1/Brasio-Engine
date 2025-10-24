#include <events/subevents/application-update.hh>

ApplicationUpdateEvent::ApplicationUpdateEvent()
    : ApplicationCategoryEvent<ApplicationUpdateEvent>(EVENT_APPLICATION_UPDATE)
{}
