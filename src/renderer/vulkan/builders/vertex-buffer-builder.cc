#include <renderer/vulkan/builders/vertex-buffer-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    VertexBufferBuilder::VertexBufferBuilder(const PhysicalDeviceType &physicalDevice,
                                             const LogicalDeviceType &logicalDevice)
        : BufferBuilder(physicalDevice, logicalDevice)
    {
        base();
    }

    VertexBufferBuilder &VertexBufferBuilder::base()
    {
        withUsage(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
            .withMemoryProperties(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        return *this;
    }
} // namespace brasio::renderer::vulkan::builders
