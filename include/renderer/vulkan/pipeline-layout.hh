#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>
#include <renderer/vulkan/descriptor-set-layout.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class PipelineLayout : public core::Handler<VkPipelineLayout>
    {
    public:
        PipelineLayout(const VulkanRenderer &renderer, DescriptorSetLayoutType descriptorSetLayout,
                       const VkPipelineLayoutCreateInfo &createInfo);

        const DescriptorSetLayout &getDescriptorSetLayout() const;

    private:
        DescriptorSetLayoutType _descriptorSetLayout;
    };

    using PipelineLayoutType = std::unique_ptr<PipelineLayout>;
} // namespace brasio::renderer::vulkan
