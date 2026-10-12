#pragma once

#include <vulkan/vulkan_core.h>

#include <memory>

#include <scenes/scene-rectangle.hh>
#include <events/event.hh>

namespace brasio::scenes
{
    class SceneNode
    {
    public:
        virtual ~SceneNode() = default;

        virtual void render(const VkCommandBuffer &commandBuffer) = 0;
        virtual void checkLayout(const SceneRectangle &sceneRectangle) = 0;
    };

    using SceneNodeType = std::unique_ptr<SceneNode>;
} // namespace brasio::scenes
