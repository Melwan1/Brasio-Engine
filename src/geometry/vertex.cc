#include <geometry/vertex.hh>

VkVertexInputBindingDescription Vertex::getBindingDescription()
{
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
}

std::array<VkVertexInputAttributeDescription, 2> Vertex::getAttributeDescriptions()
{
    std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
    VkVertexInputAttributeDescription &first = attributeDescriptions[0];
    VkVertexInputAttributeDescription &second = attributeDescriptions[1];

    first.binding = 0;
    first.location = 0;
    first.format = VK_FORMAT_R32G32B32_SFLOAT;
    first.offset = offsetof(Vertex, position);
    
    second.binding = 0;
    second.location = 1;
    second.format = VK_FORMAT_R32G32B32_SFLOAT;
    second.offset = offsetof(Vertex, color);

    return attributeDescriptions;
}