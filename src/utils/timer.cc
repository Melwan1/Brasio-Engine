#include <utils/timer.hh>

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace brasio::utils
{
    Timer::Timer(float seconds)
        : _duration(seconds)
        , _start(std::chrono::steady_clock::now())
    {}

    void Timer::reset()
    {
        _start = std::chrono::steady_clock::now();
    }

    float Timer::remaining() const
    {
        std::chrono::duration<float> elapsed = std::chrono::steady_clock::now() - _start;
        return std::clamp(_duration.count() - elapsed.count(), 0.0f, _duration.count());
    }

    bool Timer::finished() const
    {
        return remaining() <= 0.0f;
    }

    Timer::Precision Timer::precision(float remaining) const
    {
        if (remaining > 30.0f)
        {
            return Precision::SECONDS;
        }
        if (remaining > 10.0f)
        {
            return Precision::TENTHS;
        }
        return Precision::HUNDREDTHS;
    }

    std::string Timer::toString() const
    {
        float value = remaining();
        int minutes = static_cast<int>(value) / 60;
        int seconds = static_cast<int>(value) % 60;
        float fraction = value - std::floor(value);

        std::ostringstream out;
        out << std::setfill('0') << std::setw(2) << minutes << ':' << std::setw(2) << seconds;
        Precision digits = precision(value);
        if (digits == Precision::TENTHS)
        {
            out << '.' << static_cast<int>(fraction * 10.0f);
        }
        else if (digits == Precision::HUNDREDTHS)
        {
            out << '.' << std::setw(2) << static_cast<int>(fraction * 100.0f);
        }
        return out.str();
    }

    glm::vec4 Timer::color() const
    {
        float value = remaining();
        if (value > 60.0f)
        {
            return { 1.0f, 1.0f, 1.0f, 1.0f };
        }
        if (value > 30.0f)
        {
            return { 1.0f, 1.0f, 0.0f, 1.0f };
        }
        if (value > 10.0f)
        {
            return { 1.0f, 0.5f, 0.0f, 1.0f };
        }
        return { 1.0f, 0.0f, 0.0f, 1.0f };
    }

} // namespace brasio::utils
