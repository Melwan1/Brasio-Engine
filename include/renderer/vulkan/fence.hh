#pragma once

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class Fence : public core::Handler<VkFence>
    {
    public:
        Fence(const VulkanRenderer &renderer, const VkFenceCreateInfo &createInfo);
    };
} // namespace brasio::renderer::vulkan
