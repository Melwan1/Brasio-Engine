#pragma once

#include <string>

namespace brasio::scenes
{
    enum class HorizontalAlignment
    {
        LEFT = 0,
        RIGHT = 1,
        CENTER = 2,
        JUSTIFY = 3
    };

    enum class VerticalAlignment
    {
        TOP = 0,
        BOTTOM = 1,
        CENTER = 2
    };

    std::string horizontalAlignmentToString(HorizontalAlignment alignment);
    HorizontalAlignment horizontalAlignmentFromString(const std::string &alignment);

    std::string verticalAlignmentToString(VerticalAlignment alignment);
    VerticalAlignment verticalAlignmentFromString(const std::string &alignment);
} // namespace brasio::scenes
