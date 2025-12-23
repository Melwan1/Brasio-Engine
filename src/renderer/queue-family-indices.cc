#include <renderer/queue-family-indices.hh>

bool QueueFamilyIndices::isComplete()
{
    return graphicsFamily.has_value();
}