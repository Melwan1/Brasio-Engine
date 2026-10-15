#include <scenes/text-alignment.hh>

#include <io/logging/logger.hh>

#include <map>

namespace brasio::scenes
{
    std::string horizontalAlignmentToString(HorizontalAlignment alignment)
    {
        std::map<HorizontalAlignment, std::string> map = {
            { HorizontalAlignment::LEFT, "LEFT" },
            { HorizontalAlignment::RIGHT, "RIGHT" },
            { HorizontalAlignment::CENTER, "CENTER" },
            { HorizontalAlignment::JUSTIFY, "JUSTIFY" }
        };
        if (!map.contains(alignment))
        {
            BRASIO_LOG_ERROR("Unrecognized horizontal alignment", { "SCENES" });
            return "<UNKNOWN>";
        }
        return map.at(alignment);
    }

    HorizontalAlignment horizontalAlignmentFromString(const std::string &alignment)
    {
        std::map<std::string, HorizontalAlignment> map = {
            { "LEFT", HorizontalAlignment::LEFT },
            { "RIGHT", HorizontalAlignment::RIGHT },
            { "CENTER", HorizontalAlignment::CENTER },
            { "JUSTIFY", HorizontalAlignment::JUSTIFY }
        };
        if (!map.contains(alignment))
        {
            BRASIO_LOG_ERROR("Unrecognized horizontal alignment '" + alignment
                                 + "', defaulting to LEFT",
                             { "SCENES" });
            return HorizontalAlignment::LEFT;
        }
        return map.at(alignment);
    }

    std::string verticalAlignmentToString(VerticalAlignment alignment)
    {
        std::map<VerticalAlignment, std::string> map = { { VerticalAlignment::TOP, "TOP" },
                                                         { VerticalAlignment::BOTTOM, "BOTTOM" },
                                                         { VerticalAlignment::CENTER, "CENTER" } };
        if (!map.contains(alignment))
        {
            BRASIO_LOG_ERROR("Unrecognized vertical alignment", { "SCENES" });
            return "<UNKNOWN>";
        }
        return map.at(alignment);
    }

    VerticalAlignment verticalAlignmentFromString(const std::string &alignment)
    {
        std::map<std::string, VerticalAlignment> map = { { "TOP", VerticalAlignment::TOP },
                                                         { "BOTTOM", VerticalAlignment::BOTTOM },
                                                         { "CENTER", VerticalAlignment::CENTER } };
        if (!map.contains(alignment))
        {
            BRASIO_LOG_ERROR("Unrecognized vertical alignment '" + alignment
                                 + "', defaulting to CENTER",
                             { "SCENES" });
            return VerticalAlignment::CENTER;
        }
        return map.at(alignment);
    }
} // namespace brasio::scenes
