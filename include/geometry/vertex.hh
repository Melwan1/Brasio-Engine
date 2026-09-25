#pragma once

#include <glm/glm.hpp>

#include <vulkan/vulkan.hpp>

namespace brasio::geometry
{

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 color = { 0.5f, 0.5f, 0.5f };
        glm::vec3 normal = { 0.0f, 0.0f, 0.0f };
        glm::vec2 texCoord = { 0.0f, 0.0f };

        static VkVertexInputBindingDescription getBindingDescription();
        static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions();
    };
} // namespace brasio::geometry
