#pragma once

#include <events/event.hh>

template <typename CategoryType, typename SubEventType>
size_t Event<CategoryType, SubEventType>::_sequenceId = 0;

template <typename CategoryType, typename SubEventType>
size_t Event<CategoryType, SubEventType>::generateId()
{
    return _sequenceId++;
}

template <typename CategoryType, typename SubEventType>
Event<CategoryType, SubEventType>::Event(enum EventCategoryType categoryType, enum EventType eventType)
    : _id(generateId())
    , _categoryType(categoryType)
    , _eventType(eventType)
{}

template<typename CategoryType, typename SubEventType>
size_t Event<CategoryType, SubEventType>::getId() const
{
    return _id;
}

template <typename CategoryType, typename SubEventType>
enum EventCategoryType Event<CategoryType, SubEventType>::getCategoryType() const
{
    return _categoryType;
}

template <typename CategoryType, typename SubEventType>
enum EventType Event<CategoryType, SubEventType>::getType() const
{
    return _eventType;
}
