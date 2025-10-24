#include <iostream>

#include <events/libevents.hh>

int main()
{
    Event<int, int> event{ EVENT_CATEGORY_UNKNOWN, EVENT_UNKNOWN };
    std::cout << event.getId() << std::endl;
    Event<int, int> event2{ EVENT_CATEGORY_UNKNOWN, EVENT_UNKNOWN };
    std::cout << event2.getId() << std::endl;
}
