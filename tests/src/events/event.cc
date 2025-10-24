#include <gtest/gtest.h>

#include <events/libevents.hh>

TEST(Events, event_constructor_id)
{
    Event<void, void> event1(EVENT_CATEGORY_UNKNOWN, EVENT_UNKNOWN);
    Event<void, void> event2(EVENT_CATEGORY_UNKNOWN, EVENT_UNKNOWN);
    EXPECT_EQ(event2.getId() - event1.getId(), 1)
        << "Expected two successive generated events to have their id "
           "incremented by 1, got "
        << event2.getId() - event1.getId();
}

TEST(Events, event_generate_id)
{
    size_t firstId = Event<void, void>::generateId();
    size_t secondId = Event<void, void>::generateId();
    EXPECT_EQ(secondId - firstId, 1)
        << "Expected two successive generated events ids to be incremented by "
           "1, got "
        << secondId - firstId;
}
