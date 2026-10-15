#include <utils/fps-counter.hh>

#include <numeric>
#include <sstream>

namespace brasio::utils
{
    FpsCounter::FpsCounter(size_t frames)
        : _frames(frames)
        , _hasLast(false)
    {}

    void FpsCounter::tick()
    {
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        if (_hasLast)
        {
            std::chrono::duration<float> delta = now - _last;
            _durations.push_back(delta.count());
            while (_durations.size() > _frames)
            {
                _durations.pop_front();
            }
        }
        _last = now;
        _hasLast = true;
    }

    float FpsCounter::fps() const
    {
        if (_durations.empty())
        {
            return 0.0f;
        }
        float total = std::accumulate(_durations.begin(), _durations.end(), 0.0f);
        if (total <= 0.0f)
        {
            return 0.0f;
        }
        return static_cast<float>(_durations.size()) / total;
    }

    std::string FpsCounter::toString() const
    {
        std::ostringstream out;
        out << static_cast<int>(fps() + 0.5f) << " FPS";
        return out.str();
    }

} // namespace brasio::utils
