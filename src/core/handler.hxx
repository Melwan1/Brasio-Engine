#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

template <typename T>
Handler<T>::Handler(const T& handle, const std::string &objectName, const std::function<void(const T &)>& destroyFunc)
    : _handle(handle)
    , _objectName(objectName)
    , _destroyFunc(destroyFunc)
{}

template<typename T>
Handler<T>::Handler(const std::string &objectName, const std::function<void(const T &)>& destroyFunc)
    : Handler(T{}, objectName, destroyFunc)
{}

template <typename T>
Handler<T>::Handler(Handler<T> &&other) noexcept
    : _handle(std::move(other._handle))
    , _objectName(std::move(other._objectName))
    , _destroyFunc(std::move(other._destroyFunc))
{
    other._handle = VK_NULL_HANDLE;
    other._destroyFunc = [](const T&){};
}

template <typename T>
Handler<T>::~Handler()
{
    Logger::trace(std::cout, "Destroying " + _objectName, { "DESTROY" });
    _destroyFunc(_handle);
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
