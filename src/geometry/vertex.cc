#include <geometry/vertex.hh>

namespace brasio::geometry
{
    VkVertexInputBindingDescription Vertex::getBindingDescription()
    {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    std::array<VkVertexInputAttributeDescription, 3>
    Vertex::getAttributeDescriptions()
    {
        std::array<VkVertexInputAttributeDescription, 3>
            attributeDescriptions{};
        VkVertexInputAttributeDescription &position = attributeDescriptions[0];
        VkVertexInputAttributeDescription &color = attributeDescriptions[1];
        VkVertexInputAttributeDescription &texCoord = attributeDescriptions[2];

        position.binding = 0;
        position.location = 0;
        position.format = VK_FORMAT_R32G32B32_SFLOAT;
        position.offset = offsetof(Vertex, position);

        color.binding = 0;
        color.location = 1;
        color.format = VK_FORMAT_R32G32B32_SFLOAT;
        color.offset = offsetof(Vertex, color);

        texCoord.binding = 0;
        texCoord.location = 2;
        texCoord.format = VK_FORMAT_R32G32_SFLOAT;
        texCoord.offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }
} // namespace brasio::geometry
