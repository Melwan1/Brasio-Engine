#include <renderer/vulkan/builders/storage-buffer-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    StorageBufferBuilder::StorageBufferBuilder(const PhysicalDeviceType &physicalDevice,
                                               const LogicalDeviceType &logicalDevice)
        : BufferBuilder(physicalDevice, logicalDevice)
    {
        base();
    }

    StorageBufferBuilder &StorageBufferBuilder::base()
    {
        withUsage(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT
                  | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
            .withMemoryProperties(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        return *this;
    }
} // namespace brasio::renderer::vulkan::builders
