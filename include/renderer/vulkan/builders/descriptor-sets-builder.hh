#pragma once

#include <core/builder.hh>
#include <vulkan/vulkan_core.h>

#include <vector>

#include <renderer/vulkan/descriptor-sets.hh>

namespace brasio::renderer::vulkan::builders
{

    class DescriptorSetsBuilder : public core::Builder<DescriptorSetsType>
    {
    public:
        DescriptorSetsBuilder(const VkDevice &logicalDevice,
                              const VkDescriptorPool &descriptorPool);

        virtual DescriptorSetsBuilder &base() override;
        virtual DescriptorSetsType build() override;

        DescriptorSetsBuilder &withSetsCount(uint32_t setsCount);
        DescriptorSetsBuilder &
        withSetLayout(const VkDescriptorSetLayout &descriptorSetLayout);

    private:
        const VkDevice &_logicalDevice;
        const VkDescriptorPool &_descriptorPool;
        VkStructureType _structureType;

        uint32_t _setsCount;
        std::vector<VkDescriptorSetLayout> _layouts;
    };
} // namespace brasio::renderer::vulkan::builders
