#pragma once

#include <events/event-category-type.hh>
#include <events/event-type.hh>

#include <chrono>
#include <cstddef>

template <typename CategoryType, typename SubEventType>
class Event
{
public:
    Event(enum EventCategoryType categoryType, enum EventType eventType);

    static inline size_t generateId();
    inline size_t getId() const;
    inline std::chrono::steady_clock::time_point getCreationTime() const;
    inline enum EventCategoryType getCategoryType() const;
    inline enum EventType getType() const;
    inline bool getHandleStatus() const;
    void handle();

private:
    size_t _id;
    std::chrono::steady_clock::time_point _creationTime;
    enum EventCategoryType _categoryType;
    enum EventType _eventType;

    bool _handled;

    static size_t _sequenceId;
};

#include <events/event.hxx>
