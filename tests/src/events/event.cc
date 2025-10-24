#include <gtest/gtest.h>

#include <events/libevents.hh>

TEST(Events, event_constructor_id)
{
    Event<void, void> event1(EVENT_CATEGORY_UNKNOWN, EVENT_UNKNOWN);
    Event<void, void> event2(EVENT_CATEGORY_UNKNOWN, EVENT_UNKNOWN);
    EXPECT_EQ(event2.get_id() - event1.get_id(), 1)
        << "Expected two successive generated events to have their id "
           "incremented by 1, got "
        << event2.get_id() - event1.get_id();
}

TEST(Events, event_generate_id)
{
    size_t first_id = Event<void, void>::generate_id();
    size_t second_id = Event<void, void>::generate_id();
    EXPECT_EQ(second_id - first_id, 1)
        << "Expected two successive generated events id to be incremented by "
           "1, got "
        << second_id - first_id;
}
