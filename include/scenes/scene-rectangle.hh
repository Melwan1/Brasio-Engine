#pragma once

#include <yaml-cpp/yaml.h>

namespace brasio::scenes
{
    struct SceneRectangle
    {
        float top;
        float left;
        float width;
        float height;

        /** Compose this relative rectangle (fractions of the parent) against an
         *  absolute parent rectangle, producing an absolute child rectangle. */
        SceneRectangle absoluteIn(const SceneRectangle &parent) const;
    };

    YAML::Emitter &operator<<(YAML::Emitter &out, const SceneRectangle &sceneRectangle);
} // namespace brasio::scenes
