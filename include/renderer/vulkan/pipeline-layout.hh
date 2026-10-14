#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>
#include <renderer/vulkan/descriptor-set-layout.hh>

#include <vector>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class PipelineLayout : public core::Handler<VkPipelineLayout>
    {
    public:
        PipelineLayout(const VulkanRenderer &renderer,
                       std::vector<DescriptorSetLayoutType> descriptorSetLayouts,
                       const VkPipelineLayoutCreateInfo &createInfo);

        const DescriptorSetLayout &getDescriptorSetLayout(size_t index = 0) const;

    private:
        std::vector<DescriptorSetLayoutType> _descriptorSetLayouts;
    };

    using PipelineLayoutType = std::unique_ptr<PipelineLayout>;
} // namespace brasio::renderer::vulkan
