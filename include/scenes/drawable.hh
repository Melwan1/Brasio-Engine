#pragma once

#include <model/model.hh>
#include <renderer/vulkan/material.hh>
#include <scenes/transform.hh>
#include <glm/glm.hpp>
#include <yaml-cpp/yaml.h>

namespace brasio::scenes
{
    class TextLabel;

    struct Drawable
    {
        const model::Model *model{ nullptr };
        const renderer::vulkan::Material *material{ nullptr };
        Transform transform;
        glm::mat4 matrix{ 1.0f };
        const TextLabel *textLabel{ nullptr };

        void pushTransform(const VkCommandBuffer &commandBuffer) const;
        void pushText(const VkCommandBuffer &commandBuffer, const glm::vec2 &boxPixelSize) const;
    };

    YAML::Emitter &operator<<(YAML::Emitter &out, const Drawable &drawable);
} // namespace brasio::scenes
