#pragma once

#include <glm/mat4x4.hpp>

namespace brasio::renderer::structs
{

    struct UniformBufferObject
    {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };
} // namespace brasio::renderer::structs
