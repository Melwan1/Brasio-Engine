#pragma once

#include <glm/glm.hpp>
#include <yaml-cpp/yaml.h>

namespace brasio::scenes
{
    /**
     * The authored transform of a drawable.
     *
     * The rotation is stored as euler angles in degrees. These are the values
     * as written in the scene configuration, kept verbatim so serialization
     * round-trips exactly. The baked matrix is derived from them on demand via
     * matrix().
     */
    struct Transform
    {
        glm::vec3 translation{ 0.0f };
        glm::vec3 rotation{ 0.0f };
        glm::vec3 scale{ 1.0f };

        glm::mat4 matrix() const;
        bool isIdentity() const;
    };

    YAML::Emitter &operator<<(YAML::Emitter &out, const Transform &transform);
} // namespace brasio::scenes
