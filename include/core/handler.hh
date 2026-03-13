#pragma once

#include <functional>

#include <io/logging/logger.hh>

template <typename T>
class Handler
{
public:
    Handler(const T &handle, const std::string &objectName,
            const std::function<void(const T &)> &destroyFunc);

    Handler(const std::string &objectName,
            const std::function<void(const T &)> &destroyFunc);

    // Provide a custom move constructor
    Handler(Handler &&other) noexcept;

    ~Handler();

    // Delete the copy constructor and copy assignment operator
    Handler(const Handler &) = delete;
    Handler &operator=(const Handler &) = delete;

    // Delete the move assignment operator
    Handler &operator=(Handler &&) = delete;

    const T &getHandle() const;
    T &getHandle();

private:
    T _handle;
    const std::string _objectName;
    std::function<void(const T &)> _destroyFunc;
};

#include <core/handler.hxx>
