#include <renderer/vulkan/builders/uniform-buffer-builder.hh>
#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{
    UniformBufferBuilder::UniformBufferBuilder(const PhysicalDeviceType &physicalDevice,
                                               const LogicalDeviceType &logicalDevice)
        : BufferBuilder(physicalDevice, logicalDevice)
    {
        base();
    };

    UniformBufferBuilder &UniformBufferBuilder::base()
    {
        withUsage(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
            .withMemoryProperties(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
                                  | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        return *this;
    }
} // namespace brasio::renderer::vulkan::builders
