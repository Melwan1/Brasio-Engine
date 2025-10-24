#pragma once

#include <events/libevents.hh>

#include <cstddef>
#include "events/event-category-type.hh"

template <typename CategoryType, typename SubEventType>
class Event
{
public:
    Event(enum EventCategoryType categoryType, enum EventType eventType);

    static inline size_t generateId();
    inline size_t getId() const;
    inline enum EventCategoryType getCategoryType() const;
    inline enum EventType getType() const;

private:
    size_t _id;
    enum EventCategoryType _categoryType;
    enum EventType _eventType;

    static size_t _sequenceId;
};

#include <events/event.hxx>
