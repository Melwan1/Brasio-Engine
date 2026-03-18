#include <renderer/vulkan/builders/descriptor-pool-builder.hh>

namespace brasio::renderer::vulkan::builders
{

    DescriptorPoolBuilder::DescriptorPoolBuilder(const VkDevice &logicalDevice)
        : _logicalDevice(logicalDevice)
    {
        base();
    }

    DescriptorPoolBuilder &DescriptorPoolBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        _poolSizes.clear();
        return withMaxSets(0);
    }

    DescriptorPoolBuilder &DescriptorPoolBuilder::withDescriptorPoolSizes(
        const std::vector<VkDescriptorPoolSize> &poolSizes)
    {
        _poolSizes = poolSizes;
        return *this;
    }

    DescriptorPoolBuilder &DescriptorPoolBuilder::withMaxSets(uint32_t maxSets)
    {
        _maxSets = maxSets;
        return *this;
    }

    DescriptorPoolType DescriptorPoolBuilder::build()
    {
        VkDescriptorPoolCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.poolSizeCount = _poolSizes.size();
        createInfo.pPoolSizes = _poolSizes.data();
        createInfo.maxSets = _maxSets;
        return std::make_unique<DescriptorPool>(_logicalDevice, createInfo);
    }

} // namespace brasio::renderer::vulkan::builders
