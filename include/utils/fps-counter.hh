#pragma once

#include <chrono>
#include <deque>
#include <string>

namespace brasio::utils
{

    class FpsCounter
    {
    public:
        FpsCounter(size_t frames = 10);

        void tick();

        float fps() const;
        std::string toString() const;

    private:
        size_t _frames;
        std::deque<float> _durations;
        std::chrono::steady_clock::time_point _last;
        bool _hasLast;
    };

} // namespace brasio::utils
