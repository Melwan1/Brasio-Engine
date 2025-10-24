#include <iostream>

#include <events/event.hh>

int main()
{
    Event<int, int> event;
    std::cout << event.get_id() << std::endl;
    Event<int, int> event2;
    std::cout << event2.get_id() << std::endl;
}
