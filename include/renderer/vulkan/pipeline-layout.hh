#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>
#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/descriptor-set-layout.hh>

namespace brasio::renderer::vulkan
{
    class PipelineLayout : public core::Handler<VkPipelineLayout>
    {
    public:
        PipelineLayout(const VkDevice &logicalDevice, DescriptorSetLayoutType descriptorSetLayout,
                       const VkPipelineLayoutCreateInfo &createInfo);

        const DescriptorSetLayout &getDescriptorSetLayout() const;

    private:
        DescriptorSetLayoutType _descriptorSetLayout;
    };

    using PipelineLayoutType = std::unique_ptr<PipelineLayout>;
} // namespace brasio::renderer::vulkan
