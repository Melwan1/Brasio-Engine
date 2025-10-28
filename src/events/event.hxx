#pragma once

#include <io/escapes/ansi-escapes.hh>

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
}

template <typename CategoryType, typename SubEventType>
void Event<CategoryType, SubEventType>::print(std::ostream& ostr)
{
    std::time_t creationTime =
        std::chrono::system_clock::to_time_t(getCreationTime());
    std::tm local_time = *std::localtime(&creationTime);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  getCreationTime().time_since_epoch())
        % 1000;
    std::ostringstream oss;
    oss << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");

    std::chrono::system_clock::time_point now =
        std::chrono::system_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - getCreationTime());

    ostr << FG_ESC(244) << "[" << oss.str() << "."
              << std::format("{:03}", ms.count());
    ostr << FG_ESC(15) << " in " << FG_ESC(76) << std::setw(3)
              << std::setfill(' ') << duration.count() << FG_ESC(15) << " ms";
    ostr << "]" << FG_ESC(15) << " Handling " << getTypeName();
}
