#include <renderer/vulkan/builders/staging-buffer-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    StagingBufferBuilder::StagingBufferBuilder(const PhysicalDeviceType &physicalDevice,
                                               const LogicalDeviceType &logicalDevice)
        : BufferBuilder(physicalDevice, logicalDevice)
    {
        base();
    }

    StagingBufferBuilder &StagingBufferBuilder::base()
    {
        withUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
            .withMemoryProperties(VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        return *this;
    }
} // namespace brasio::renderer::vulkan::builders
