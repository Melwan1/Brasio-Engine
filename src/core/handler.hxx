#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

template <typename T>
Handler<T>::Handler(const T& handle, const std::string &objectName, const std::function<void()>& destroyFunc)
    : _handle(handle)
    , _objectName(objectName)
    , _destroyFunc(destroyFunc)
{}

template <typename T>
Handler<T>::Handler(Handler<T> &&other) noexcept
    : _handle(std::move(other.handle))
{
    other._handle = VK_NULL_HANDLE;
}

template <typename T>
Handler<T>::~Handler()
{
    Logger::trace(std::cout, "Destroying " + _objectName, { "DESTROY" });
    _destroyFunc();
    Logger::trace(std::cout, "Destroyed " + _objectName, { "DESTROY" });
}

template <typename T>
const T& Handler<T>::getHandle() const
{
    return _handle;
}

template <typename T>
T& Handler<T>::getHandle()
{
    return _handle;
}
