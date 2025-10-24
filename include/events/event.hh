#pragma once

#include <cstddef>

template <typename EventCategoryType, typename EventType>
class Event
{
public:
    Event();

    static inline size_t generate_id();
    inline size_t get_id() const;

private:
    size_t _id{};
    static size_t _sequence_id;
};

#include <events/event.hxx>
