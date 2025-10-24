#pragma once

#include <events/event.hh>

template <typename EventCategoryType, typename EventType>
size_t Event<EventCategoryType, EventType>::_sequence_id = 0;

template <typename EventCategoryType, typename EventType>
size_t Event<EventCategoryType, EventType>::generate_id()
{
    return _sequence_id++;
}

template<typename EventCategoryType, typename EventType>
size_t Event<EventCategoryType, EventType>::get_id() const
{
    return _id;
}

template <typename EventCategoryType, typename EventType>
Event<EventCategoryType, EventType>::Event()
    : _id(generate_id())
{}
