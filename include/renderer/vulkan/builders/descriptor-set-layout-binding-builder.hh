#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{

    class DescriptorSetLayoutBindingBuilder
        : public core::Builder<VkDescriptorSetLayoutBinding>
    {
    public:
        DescriptorSetLayoutBindingBuilder();

        virtual VkDescriptorSetLayoutBinding build() override;
        virtual DescriptorSetLayoutBindingBuilder &base() override;

        DescriptorSetLayoutBindingBuilder &
        withBindingIndex(uint32_t bindingIndex);
        DescriptorSetLayoutBindingBuilder &
        withDescriptorType(const VkDescriptorType &descriptorType);
        DescriptorSetLayoutBindingBuilder &
        withDescriptorCount(uint32_t descriptorCount);
        DescriptorSetLayoutBindingBuilder &
        withShaderStages(const VkShaderStageFlags &shaderStages);

    private:
        uint32_t _bindingIndex;
        VkDescriptorType _descriptorType;
        uint32_t _descriptorCount;
        VkShaderStageFlags _shaderStages;
    };
} // namespace brasio::renderer::vulkan::builders
