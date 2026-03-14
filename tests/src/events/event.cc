#include <gtest/gtest.h>

#include <events/libevents.hh>
#include "events/event-category-type.hh"

TEST(Events_Event_Identifiers, constructor)
{
    brasio::events::subevents::UnknownEvent event1;
    brasio::events::subevents::UnknownEvent event2;
    EXPECT_EQ(event2.getId() - event1.getId(), 1)
        << "Expected two successive generated events to have their id "
           "incremented by 1, got "
        << event2.getId() - event1.getId();
}

TEST(Events_Event_Identifiers, generation)
{
    size_t firstId = brasio::events::subevents::UnknownEvent::generateId();
    size_t secondId = brasio::events::subevents::UnknownEvent::generateId();
    EXPECT_EQ(secondId - firstId, 1)
        << "Expected two successive generated events ids to be incremented by "
           "1, got "
        << secondId - firstId;
}

TEST(Events_Event_CategoryType, keyboard)
{
    enum brasio::events::EventCategoryType categoryType =
        brasio::events::EVENT_CATEGORY_KEYBOARD;
    brasio::events::subevents::KeyboardPressEvent event("A");
    EXPECT_EQ(event.getCategoryType(), categoryType);
}

TEST(Events_Event_CategoryType, unknown)
{
    enum brasio::events::EventCategoryType categoryType =
        brasio::events::EVENT_CATEGORY_UNKNOWN;
    brasio::events::subevents::UnknownEvent event;
    EXPECT_EQ(event.getCategoryType(), categoryType);
}

TEST(Events_Event_EventType, keyboardPress)
{
    enum brasio::events::EventType eventType =
        brasio::events::EVENT_KEYBOARD_PRESS;
    brasio::events::subevents::KeyboardPressEvent event("A");
    EXPECT_EQ(event.getType(), eventType);
}

TEST(Events_Event_EventType, unknown)
{
    enum brasio::events::EventType eventType = brasio::events::EVENT_UNKNOWN;
    brasio::events::subevents::UnknownEvent event;
    EXPECT_EQ(event.getType(), eventType);
}

TEST(Events_Event_CreationTime, unknown)
{
    std::chrono::system_clock::time_point start =
        std::chrono::system_clock::now();

    brasio::events::subevents::UnknownEvent event;

    std::chrono::system_clock::time_point end =
        std::chrono::system_clock::now();

    EXPECT_GE(event.getCreationTime(), start);
    EXPECT_LE(event.getCreationTime(), end);
}

TEST(Events_Event_CreationTime, keyboardLongPress)
{
    std::chrono::system_clock::time_point start =
        std::chrono::system_clock::now();

    brasio::events::subevents::KeyboardLongPressEvent event("A", 1);

    std::chrono::system_clock::time_point end =
        std::chrono::system_clock::now();

    EXPECT_GE(event.getCreationTime(), start);
    EXPECT_LE(event.getCreationTime(), end);
}

TEST(Events_Event_Handle_Unhandled, unknown)
{
    brasio::events::subevents::UnknownEvent event;
    EXPECT_FALSE(event.getHandleStatus());
}

TEST(Events_Event_Handle_Unhandled, mouseMove)
{
    brasio::events::subevents::MouseMoveEvent event(14, 28);
    EXPECT_FALSE(event.getHandleStatus());
}

TEST(Events_Event_Handle_Handled, unknown)
{
    brasio::events::subevents::UnknownEvent event;
    event.handle();
    EXPECT_TRUE(event.getHandleStatus());
}

TEST(Events_Event_Handle_Handled, mouseMove)
{
    brasio::events::subevents::MouseMoveEvent event(14, 28);
    event.handle();
    EXPECT_TRUE(event.getHandleStatus());
}
