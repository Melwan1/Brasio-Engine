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

    private:
        uint32_t _descriptorCount;
    };
} // namespace brasio::renderer::vulkan::builders
