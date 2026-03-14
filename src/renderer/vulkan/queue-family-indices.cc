#include <renderer/vulkan/queue-family-indices.hh>

namespace brasio::renderer::vulkan
{
    bool QueueFamilyIndices::isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
} // namespace brasio::renderer::vulkan
