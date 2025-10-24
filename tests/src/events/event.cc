#include <gtest/gtest.h>

#include <events/libevents.hh>
#include "events/event-category-type.hh"

TEST(Events, eventConstructorId)
{
    Event<void, void> event1(EVENT_CATEGORY_UNKNOWN, EVENT_UNKNOWN);
    Event<void, void> event2(EVENT_CATEGORY_UNKNOWN, EVENT_UNKNOWN);
    EXPECT_EQ(event2.getId() - event1.getId(), 1)
        << "Expected two successive generated events to have their id "
           "incremented by 1, got "
        << event2.getId() - event1.getId();
}

TEST(Events, eventGenerateId)
{
    size_t firstId = Event<void, void>::generateId();
    size_t secondId = Event<void, void>::generateId();
    EXPECT_EQ(secondId - firstId, 1)
        << "Expected two successive generated events ids to be incremented by "
           "1, got "
        << secondId - firstId;
}

TEST(Events, eventCategoryTypeKeyboard)
{
    enum EventCategoryType categoryType = EVENT_CATEGORY_KEYBOARD;
    enum EventType eventType = EVENT_KEYBOARD_PRESS;
    Event<void, void> event1(categoryType, eventType);
    EXPECT_EQ(event1.getCategoryType(), categoryType);
}

TEST(Events, eventCategoryTypeUnknown)
{
    enum EventCategoryType categoryType = EVENT_CATEGORY_UNKNOWN;
    enum EventType eventType = EVENT_UNKNOWN;
    Event<void, void> event1(categoryType, eventType);
    EXPECT_EQ(event1.getCategoryType(), categoryType);
}

TEST(Events, eventTypeKeyboardPress)
{
    enum EventCategoryType categoryType = EVENT_CATEGORY_KEYBOARD;
    enum EventType eventType = EVENT_KEYBOARD_PRESS;
    Event<void, void> event1(categoryType, eventType);
    EXPECT_EQ(event1.getType(), eventType);
}

TEST(Events, eventTypeUnknown)
{
    enum EventCategoryType categoryType = EVENT_CATEGORY_UNKNOWN;
    enum EventType eventType = EVENT_UNKNOWN;
    Event<void, void> event1(categoryType, eventType);
    EXPECT_EQ(event1.getType(), eventType);
}
