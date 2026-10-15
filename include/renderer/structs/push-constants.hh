#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

namespace brasio::renderer::structs
{

    struct PushConstants
    {
        glm::mat4 model;
        glm::vec4 color;
    };
} // namespace brasio::renderer::structs
