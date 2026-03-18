#include <renderer/vulkan/builders/descriptor-pool-size-builder.hh>

namespace brasio::renderer::vulkan::builders
{

    DescriptorPoolSizeBuilder::DescriptorPoolSizeBuilder()
    {
        base();
    }

    DescriptorPoolSizeBuilder &DescriptorPoolSizeBuilder::base()
    {
        return withDescriptorCount(0);
    }

    VkDescriptorPoolSize DescriptorPoolSizeBuilder::build()
    {
        VkDescriptorPoolSize poolSize{};
        poolSize.descriptorCount = _descriptorCount;
        poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        return poolSize;
    }

    DescriptorPoolSizeBuilder &
    DescriptorPoolSizeBuilder::withDescriptorCount(uint32_t descriptorCount)
    {
        _descriptorCount = descriptorCount;
        return *this;
    }

} // namespace brasio::renderer::vulkan::builders
