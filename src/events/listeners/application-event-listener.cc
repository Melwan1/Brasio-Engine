#include <events/listeners/application-event-listener.hh>

#include <iostream>

void ApplicationEventListener::onEvent(ApplicationRenderEvent &event)
{
    event.print(std::cout);
    std::cout << "\n";
    event.handle();
}

void ApplicationEventListener::onEvent(ApplicationTickEvent &event)
{
    event.print(std::cout);
    std::cout << "\n";
    event.handle();
}

void ApplicationEventListener::onEvent(ApplicationUpdateEvent &event)
{
    event.print(std::cout);
    std::cout << "\n";
    event.handle();
}
