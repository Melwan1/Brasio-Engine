#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

namespace brasio::renderer::vulkan
{
    class DescriptorPool : public core::Handler<VkDescriptorPool>
    {
    public:
        DescriptorPool(const VkDevice &logicalDevice,
                       const VkDescriptorPoolCreateInfo &createInfo);
    };

    using DescriptorPoolType = std::unique_ptr<DescriptorPool>;
} // namespace brasio::renderer::vulkan
