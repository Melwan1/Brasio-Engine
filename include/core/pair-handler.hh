#pragma once

#include <functional>
#include <string>

#include <io/logging/logger.hh>

namespace brasio::core {

    template <typename T1, typename T2>
    class PairHandler
    {
        public:
            PairHandler(const T1 &handle1, const T2 &handle2, const std::string &objectName1, const std::string &objectName2, const std::function<void(const T1&)> &destroyFunc1, const std::function<void(const T2&)> &destroyFunc2);

            PairHandler(const std::string &objectName1, const std::string &objectName2, const std::function<void(const T1 &)> &destroyFunc1, const std::function<void(const T2 &)> &destroyFunc2);

            PairHandler(PairHandler &&other) noexcept;

            ~PairHandler();

            PairHandler(const PairHandler &) = delete;
            PairHandler &operator=(const PairHandler &) = delete;

            PairHandler &operator=(PairHandler &&other) = delete;

            const T1 &getHandle1() const;
            const T2 &getHandle2() const;

            T1 &getHandle1();
            T2 &getHandle2();

        private:

            T1 _handle1;
            T2 _handle2;

            const std::string _objectName1;
            const std::string _objectName2;

            std::function<void(const T1 &)> _destroyFunc1;
            std::function<void(const T2 &)> _destroyFunc2;
            
    };

}

#include <core/pair-handler.hxx>
