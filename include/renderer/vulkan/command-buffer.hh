#pragma once

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>
#include <renderer/vulkan/logical-device.hh>

namespace brasio::renderer::vulkan
{

    class CommandBuffer : public core::Handler<VkCommandBuffer>
    {
    public:
        CommandBuffer(const LogicalDeviceType &logicalDevice,
                      const VkCommandPool &comandPool);

        void begin();
        void end();

    private:
        bool _ended;
        const LogicalDeviceType &_logicalDevice;
        const VkCommandPool &_commandPool;
    };
} // namespace brasio::renderer::vulkan
