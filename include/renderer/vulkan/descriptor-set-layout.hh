#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

namespace brasio::renderer::vulkan
{

    class DescriptorSetLayout : public core::Handler<VkDescriptorSetLayout>
    {
    public:
        DescriptorSetLayout(const VkDevice &logicalDevice,
                            const VkDescriptorSetLayoutCreateInfo &createInfo);
    };

    using DescriptorSetLayoutType = std::unique_ptr<DescriptorSetLayout>;

} // namespace brasio::renderer::vulkan
