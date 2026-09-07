#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{

    class DescriptorPoolSizeBuilder : public core::Builder<VkDescriptorPoolSize>
    {
    public:
        DescriptorPoolSizeBuilder();

        virtual DescriptorPoolSizeBuilder &base() override;
        virtual VkDescriptorPoolSize build() override;

        DescriptorPoolSizeBuilder &
        withDescriptorCount(uint32_t descriptorCount);

        DescriptorPoolSizeBuilder &withDescriptorType(VkDescriptorType descriptorType);

    private:
        uint32_t _descriptorCount;
        VkDescriptorType _descriptorType;
    };
} // namespace brasio::renderer::vulkan::builders
