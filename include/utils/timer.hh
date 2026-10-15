#pragma once

#include <chrono>
#include <string>

#include <glm/glm.hpp>

namespace brasio::utils
{

    class Timer
    {
    public:
        Timer(float seconds);

        void reset();

        float remaining() const;
        bool finished() const;

        std::string toString() const;
        glm::vec4 color() const;

    private:
        enum class Precision
        {
            SECONDS = 0,
            TENTHS = 1,
            HUNDREDTHS = 2
        };

        Precision precision(float remaining) const;

        std::chrono::duration<float> _duration;
        std::chrono::steady_clock::time_point _start;
    };

} // namespace brasio::utils
