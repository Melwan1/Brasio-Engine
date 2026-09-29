#include <renderer/vulkan/builders/vertex-input-builder.hh>

#include <cstddef>

#include <renderer/structs/particle.hh>

namespace brasio::renderer::vulkan::builders
{
    VertexInputBuilder::VertexInputBuilder()
    {
        base();
    }

    VertexInputBuilder &VertexInputBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        std::array<VkVertexInputAttributeDescription, 4> attributeDescriptions =
            geometry::Vertex::getAttributeDescriptions();
        return withBindingDescriptions({ geometry::Vertex::getBindingDescription() })
            .withAttributeDescriptions(
                { attributeDescriptions.begin(), attributeDescriptions.end() });
    }

    VertexInputBuilder &VertexInputBuilder::withParticleInput()
    {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(structs::Particle);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        VkVertexInputAttributeDescription position{};
        position.binding = 0;
        position.location = 0;
        position.format = VK_FORMAT_R32G32_SFLOAT;
        position.offset = offsetof(structs::Particle, position);

        VkVertexInputAttributeDescription color{};
        color.binding = 0;
        color.location = 1;
        color.format = VK_FORMAT_R32G32B32A32_SFLOAT;
        color.offset = offsetof(structs::Particle, color);

        return withBindingDescriptions({ bindingDescription })
            .withAttributeDescriptions({ position, color });
    }

    VkPipelineVertexInputStateCreateInfo VertexInputBuilder::build()
    {
        VkPipelineVertexInputStateCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.vertexBindingDescriptionCount = _bindingDescriptions.size();
        createInfo.pVertexBindingDescriptions = _bindingDescriptions.data();
        createInfo.vertexAttributeDescriptionCount = _attributeDescriptions.size();
        createInfo.pVertexAttributeDescriptions = _attributeDescriptions.data();
        return createInfo;
    }

    VertexInputBuilder &VertexInputBuilder::withBindingDescriptions(
        const std::vector<VkVertexInputBindingDescription> &bindingDescriptions)
    {
        _bindingDescriptions = bindingDescriptions;
        return *this;
    }

    VertexInputBuilder &VertexInputBuilder::withAttributeDescriptions(
        const std::vector<VkVertexInputAttributeDescription> &attributeDescriptions)
    {
        _attributeDescriptions = attributeDescriptions;
        return *this;
    }
} // namespace brasio::renderer::vulkan::builders
