#pragma once

#include <model/model.hh>
#include <renderer/vulkan/material.hh>
#include <glm/glm.hpp>
#include <yaml-cpp/yaml.h>

namespace brasio::scenes
{
    struct Drawable
    {
        const model::Model *model;
        const renderer::vulkan::Material *material;
        glm::mat4 transform;

        void pushTransform(const VkCommandBuffer &commandBuffer) const;
    };

    YAML::Emitter &operator<<(YAML::Emitter &out, const Drawable &drawable);
} // namespace brasio::scenes
