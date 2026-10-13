#pragma once

#include <vulkan/vulkan_core.h>

#include <cstdint>

namespace brasio::renderer
{
    /**
     * An interface for anything that can record draw commands into a command
     * buffer.
     *
     * This lives in the renderer layer so the renderer can drive rendering
     * without depending on the scenes library. Scene nodes implement this
     * interface, which keeps the dependency pointing from scenes to the
     * renderer only.
     */
    class Renderable
    {
    public:
        virtual ~Renderable() = default;

        virtual void checkLayout(uint32_t width, uint32_t height) = 0;

        virtual void render(const VkCommandBuffer &commandBuffer) = 0;
    };
} // namespace brasio::renderer
