#pragma once

#include <events/libevents.hh>

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
    , _creationTime(std::chrono::steady_clock::now())
    , _categoryType(categoryType)
    , _eventType(eventType)
    , _handled(false)
{}

template<typename CategoryType, typename SubEventType>
size_t Event<CategoryType, SubEventType>::getId() const
{
    return _id;
}

template<typename CategoryType, typename SubEventType>
std::chrono::steady_clock::time_point Event<CategoryType, SubEventType>::getCreationTime() const
{
    return _creationTime;
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

template <typename CategoryType, typename SubEventType>
bool Event<CategoryType, SubEventType>::getHandleStatus() const
{
    return _handled;
}

template <typename CategoryType, typename SubEventType>
void Event<CategoryType, SubEventType>::handle()
{
    _handled = true;
}
