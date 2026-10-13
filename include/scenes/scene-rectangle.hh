#pragma once

#include <yaml-cpp/yaml.h>

namespace brasio::scenes
{
    struct SceneRectangle
    {
        unsigned top;
        unsigned left;
        unsigned width;
        unsigned height;
    };

    YAML::Emitter &operator<<(YAML::Emitter &out, const SceneRectangle &sceneRectangle);
} // namespace brasio::scenes
