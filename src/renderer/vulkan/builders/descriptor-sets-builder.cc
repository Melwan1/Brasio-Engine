#include <renderer/vulkan/builders/descriptor-sets-builder.hh>

namespace brasio::renderer::vulkan::builders
{

    DescriptorSetsBuilder::DescriptorSetsBuilder(
        const VkDevice &logicalDevice, const VkDescriptorPool &descriptorPool)
        : _logicalDevice(logicalDevice)
        , _descriptorPool(descriptorPool)
    {
        base();
    }

    DescriptorSetsBuilder &DescriptorSetsBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        _layouts.clear();
        return withSetsCount(0);
    }

    DescriptorSetsType DescriptorSetsBuilder::build()
    {
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = _structureType;
        allocInfo.descriptorPool = _descriptorPool;
        allocInfo.descriptorSetCount = _setsCount;
        allocInfo.pSetLayouts = _layouts.data();

        return std::make_unique<DescriptorSets>(_logicalDevice, allocInfo);
    }

    DescriptorSetsBuilder &
    DescriptorSetsBuilder::withSetsCount(uint32_t setsCount)
    {
        _setsCount = setsCount;
        return *this;
    }

    DescriptorSetsBuilder &DescriptorSetsBuilder::withSetLayout(
        const VkDescriptorSetLayout &descriptorSetLayout)
    {
        _layouts.resize(_setsCount, descriptorSetLayout);
        return *this;
    }

} // namespace brasio::renderer::vulkan::builders
