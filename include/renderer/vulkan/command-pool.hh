#pragma once

#include <core/handler.hh>

#include <memory>

namespace brasio::renderer::vulkan
{
    class CommandPool : public core::Handler<VkCommandPool>
    {
    public:
        CommandPool(const VkDevice &logicalDevice,
                    const VkCommandPoolCreateInfo &createInfo);
    };

    using CommandPoolType = std::unique_ptr<CommandPool>;
} // namespace brasio::renderer::vulkan
