#pragma once

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>

namespace brasio::renderer::vulkan
{

    class VulkanRenderer;

    class CommandBuffer : public core::Handler<VkCommandBuffer>
    {
    public:
        CommandBuffer(const VulkanRenderer &renderer);

        void begin();
        void end();

    private:
        bool _ended;
        const VulkanRenderer &_renderer;
    };
} // namespace brasio::renderer::vulkan
