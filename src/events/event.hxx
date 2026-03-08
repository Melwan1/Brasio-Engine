#pragma once

#include <iostream>

#include <io/escapes/ansi-escapes.hh>
#include <io/logging/logger.hh>

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
    , _creationTime(std::chrono::system_clock::now())
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
std::chrono::system_clock::time_point Event<CategoryType, SubEventType>::getCreationTime() const
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
    print(std::cout);
}

template <typename CategoryType, typename SubEventType>
void Event<CategoryType, SubEventType>::print(std::ostream& ostr)
{
    std::chrono::system_clock::time_point now =
        std::chrono::system_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        now - getCreationTime());

    std::ostringstream oss;
    oss << "Duration: " << FG_ESC(76) << std::setw(5) << std::setfill(' ') << duration.count() << " us" << ESC_RESET;
    Logger::trace(ostr, "Handling " + getTypeName(), {"EVENT", oss.str()});
    
}

template <typename CategoryType, typename SubEventType>
Event<CategoryType, SubEventType>::~Event()
{
    if (!_handled)
    {
        Logger::warning(std::cout, "Destroying event of type " + std::to_string(getType()) + " without handling it", { "EVENT" } );
    }
}
