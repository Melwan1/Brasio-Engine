#pragma once

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>

namespace brasio::renderer::vulkan
{
    class Fence : public core::Handler<VkFence>
    {
    public:
        Fence(const VkDevice &logicalDevice,
              const VkFenceCreateInfo &createInfo);
    };
} // namespace brasio::renderer::vulkan
