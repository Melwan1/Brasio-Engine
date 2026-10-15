#pragma once

#include <string>

namespace brasio::scenes
{
    enum DrawTarget
    {
        SCREEN = 0,
        OFFSCREEN = 1
    };

    std::string drawTargetToString(DrawTarget drawTarget);
} // namespace brasio::scenes
