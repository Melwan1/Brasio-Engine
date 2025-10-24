#pragma once

#include <events/libevents.hh>

#include <cstddef>
#include "events/event-category-type.hh"

template <typename CategoryType, typename SubEventType>
class Event
{
public:
    Event(enum EventCategoryType categoryType, enum EventType eventType);

    static inline size_t generate_id();
    inline size_t get_id() const;

private:
    size_t _id{};

    enum EventCategoryType _categoryType;
    enum EventType _eventType;

    static size_t _sequence_id;
};

#include <events/event.hxx>
