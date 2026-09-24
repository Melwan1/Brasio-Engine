#pragma once

#include <core/pair-handler.hh>

#include <vulkan/vulkan_core.h>

namespace brasio::core
{

    template <typename T1, typename T2>
    PairHandler<T1, T2>::PairHandler(
        const T1 &handle1, const T2 &handle2, const std::string &objectName1,
        const std::string &objectName2,
        const std::function<void(const T1 &)> &destroyFunc1,
        const std::function<void(const T2 &)> &destroyFunc2)
        : _handle1(handle1)
        , _handle2(handle2)
        , _objectName1(objectName1)
        , _objectName2(objectName2)
        , _destroyFunc1(destroyFunc1)
        , _destroyFunc2(destroyFunc2)
    {}

    template <typename T1, typename T2>
    PairHandler<T1, T2>::PairHandler(
        const std::string &objectName1, const std::string &objectName2,
        const std::function<void(const T1 &)> &destroyFunc1,
        const std::function<void(const T2 &)> &destroyFunc2)
        : PairHandler(T1{}, T2{}, objectName1, objectName2, destroyFunc1,
                      destroyFunc2)
    {}

    template <typename T1, typename T2>
    PairHandler<T1, T2>::PairHandler(PairHandler<T1, T2> &&other) noexcept
        : _handle1(other._handle1)
        , _handle2(other._handle2)
        , _objectName1(other._objectName1)
        , _objectName2(other._objectName2)
        , _destroyFunc1(other._destroyFunc1)
        , _destroyFunc2(other._destroyFunc2)
    {
        other._handle1 = VK_NULL_HANDLE;
        other._handle2 = VK_NULL_HANDLE;
        other._destroyFunc1 = [](const T1 &) {};
        other._destroyFunc2 = [](const T2 &) {};
    }

    template <typename T1, typename T2>
    PairHandler<T1, T2>::~PairHandler()
    {
        BRASIO_LOG_TRACE("Destroying " + _objectName1, { "DESTROY" });
        _destroyFunc1(_handle1);
        _handle1 = VK_NULL_HANDLE;
        BRASIO_LOG_TRACE("Destroyed " + _objectName1, { "DESTROY" });
        BRASIO_LOG_TRACE("Destroying " + _objectName2, { "DESTROY" });
        _destroyFunc2(_handle2);
        _handle2 = VK_NULL_HANDLE;
        BRASIO_LOG_TRACE("Destroyed " + _objectName2, { "DESTROY" });
    }

    template <typename T1, typename T2>
    const T1 &PairHandler<T1, T2>::getHandle1() const
    {
        return _handle1;
    }

    template <typename T1, typename T2>
    T1 &PairHandler<T1, T2>::getHandle1()
    {
        return _handle1;
    }

    template <typename T1, typename T2>
    const T2 &PairHandler<T1, T2>::getHandle2() const
    {
        return _handle2;
    }

    template <typename T1, typename T2>
    T2 &PairHandler<T1, T2>::getHandle2()
    {
        return _handle2;
    }

} // namespace brasio::core
