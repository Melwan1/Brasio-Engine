#pragma once

#include <mesh/mesh.hh>
#include <renderer/vulkan/material.hh>
#include <glm/glm.hpp>

namespace brasio::scenes
{
    struct Drawable
    {
        const mesh::Mesh *mesh;
        const renderer::vulkan::Material *material;
        glm::mat4 transform;

        void pushTransform(const VkCommandBuffer &commandBuffer) const;
    };
} // namespace brasio::scenes
