#include <renderer/vulkan/builders/descriptor-pool-size-builder.hh>

namespace brasio::renderer::vulkan::builders
{

    DescriptorPoolSizeBuilder::DescriptorPoolSizeBuilder()
    {
        base();
    }

    DescriptorPoolSizeBuilder &DescriptorPoolSizeBuilder::base()
    {
        return withDescriptorCount(0).withDescriptorType(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
    }

    VkDescriptorPoolSize DescriptorPoolSizeBuilder::build()
    {
        VkDescriptorPoolSize poolSize{};
        poolSize.descriptorCount = _descriptorCount;
        poolSize.type = _descriptorType;
        return poolSize;
    }

    DescriptorPoolSizeBuilder &
    DescriptorPoolSizeBuilder::withDescriptorCount(uint32_t descriptorCount)
    {
        _descriptorCount = descriptorCount;
        return *this;
    }

    DescriptorPoolSizeBuilder &
    DescriptorPoolSizeBuilder::withDescriptorType(VkDescriptorType descriptorType)
    {
        _descriptorType = descriptorType;
        return *this;
    }

} // namespace brasio::renderer::vulkan::builders
