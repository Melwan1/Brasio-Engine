#pragma once

#include <core/handler.hh>

#include <memory>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class CommandPool : public core::Handler<VkCommandPool>
    {
    public:
        CommandPool(const VulkanRenderer &renderer, const VkCommandPoolCreateInfo &createInfo);
    };

    using CommandPoolType = std::unique_ptr<CommandPool>;
} // namespace brasio::renderer::vulkan
