#include <scenes/draw-target.hh>

#include <io/logging/logger.hh>

#include <map>

namespace brasio::scenes
{
    std::string drawTargetToString(DrawTarget drawTarget)
    {
        std::map<DrawTarget, std::string> map = { { SCREEN, "SCREEN" },
                                                  { OFFSCREEN, "OFFSCREEN" } };
        if (!map.contains(drawTarget))
        {
            BRASIO_LOG_ERROR("Unrecognized draw target: " + std::to_string(drawTarget),
                             { "SCENES" });
            return "<UNKNOWN>";
        }
        return map.at(drawTarget);
    }
} // namespace brasio::scenes
