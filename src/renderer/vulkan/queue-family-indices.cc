#include <renderer/vulkan/queue-family-indices.hh>

bool QueueFamilyIndices::isComplete()
{
    return graphicsFamily.has_value() && presentFamily.has_value();
}
