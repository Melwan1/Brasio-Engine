#include <renderer/vulkan/builders/index-buffer-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    IndexBufferBuilder::IndexBufferBuilder(const PhysicalDeviceType &physicalDevice,
                                           const LogicalDeviceType &logicalDevice)
        : BufferBuilder(physicalDevice, logicalDevice)
    {
        base();
    }

    IndexBufferBuilder &IndexBufferBuilder::base()
    {
        withUsage(VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
            .withMemoryProperties(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        return *this;
    }
} // namespace brasio::renderer::vulkan::builders
