#include <gtest/gtest.h>

#include <events/libevents.hh>
#include "events/event-category-type.hh"

TEST(Events_Event_Identifiers, constructor)
{
    UnknownEvent event1;
    UnknownEvent event2;
    EXPECT_EQ(event2.getId() - event1.getId(), 1)
        << "Expected two successive generated events to have their id "
           "incremented by 1, got "
        << event2.getId() - event1.getId();
}

TEST(Events_Event_Identifiers, generation)
{
    size_t firstId = UnknownEvent::generateId();
    size_t secondId = UnknownEvent::generateId();
    EXPECT_EQ(secondId - firstId, 1)
        << "Expected two successive generated events ids to be incremented by "
           "1, got "
        << secondId - firstId;
}

TEST(Events_Event_CategoryType, keyboard)
{
    enum EventCategoryType categoryType = EVENT_CATEGORY_KEYBOARD;
    KeyboardPressEvent event;
    EXPECT_EQ(event.getCategoryType(), categoryType);
}

TEST(Events_Event_CategoryType, unknown)
{
    enum EventCategoryType categoryType = EVENT_CATEGORY_UNKNOWN;
    UnknownEvent event;
    EXPECT_EQ(event.getCategoryType(), categoryType);
}

TEST(Events_Event_EventType, keyboardPress)
{
    enum EventType eventType = EVENT_KEYBOARD_PRESS;
    KeyboardPressEvent event;
    EXPECT_EQ(event.getType(), eventType);
}

TEST(Events_Event_EventType, unknown)
{
    enum EventType eventType = EVENT_UNKNOWN;
    UnknownEvent event;
    EXPECT_EQ(event.getType(), eventType);
}

TEST(Events_Event_CreationTime, unknown)
{
    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();

    UnknownEvent event;

    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();

    EXPECT_GE(event.getCreationTime(), start);
    EXPECT_LE(event.getCreationTime(), end);
}

TEST(Events_Event_CreationTime, keyboardLongPress)
{
    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();

    KeyboardLongPressEvent event;

    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();

    EXPECT_GE(event.getCreationTime(), start);
    EXPECT_LE(event.getCreationTime(), end);
}
