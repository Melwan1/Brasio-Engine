#include <events/listeners/application-event-listener.hh>

#include <iostream>

namespace brasio::events::listeners
{
    void
    ApplicationEventListener::onEvent(subevents::ApplicationRenderEvent &event)
    {
        event.print(std::cout);
        std::cout << "\n";
        event.handle();
    }

    void
    ApplicationEventListener::onEvent(subevents::ApplicationTickEvent &event)
    {
        event.print(std::cout);
        std::cout << "\n";
        event.handle();
    }

    void
    ApplicationEventListener::onEvent(subevents::ApplicationUpdateEvent &event)
    {
        event.print(std::cout);
        std::cout << "\n";
        event.handle();
    }
} // namespace brasio::events::listeners
