#pragma once

#include <core/builder.hh>

#include <renderer/vulkan/builders/descriptor-pool-size-builder.hh>
#include <renderer/vulkan/descriptor-pool.hh>

namespace brasio::renderer::vulkan::builders
{

    class DescriptorPoolBuilder : public core::Builder<DescriptorPoolType>
    {
    public:
        DescriptorPoolBuilder(const VkDevice &logicalDevice);

        virtual DescriptorPoolBuilder &base() override;
        virtual DescriptorPoolType build() override;

        DescriptorPoolBuilder &withDescriptorPoolSizes(
            const std::vector<VkDescriptorPoolSize> &poolSizes);

        DescriptorPoolBuilder &withMaxSets(uint32_t maxSets);

    private:
        VkDevice _logicalDevice;
        VkStructureType _structureType;
        std::vector<VkDescriptorPoolSize> _poolSizes;
        uint32_t _maxSets;
    };

} // namespace brasio::renderer::vulkan::builders
