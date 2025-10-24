#pragma once

#include <events/event.hh>

template <typename CategoryType, typename SubEventType>
size_t Event<CategoryType, SubEventType>::_sequence_id = 0;

template <typename CategoryType, typename SubEventType>
size_t Event<CategoryType, SubEventType>::generate_id()
{
    return _sequence_id++;
}

template<typename CategoryType, typename SubEventType>
size_t Event<CategoryType, SubEventType>::get_id() const
{
    return _id;
}

template <typename CategoryType, typename SubEventType>
Event<CategoryType, SubEventType>::Event(enum EventCategoryType categoryType, enum EventType eventType)
    : _id(generate_id())
    , _categoryType(categoryType)
    , _eventType(eventType)
{}
