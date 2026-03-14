#include <renderer/vulkan/builders/vertex-input-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    VertexInputBuilder::VertexInputBuilder()
    {
        base();
    }

    VertexInputBuilder &VertexInputBuilder::base()
    {
        _structureType =
            VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        return withBindingDescriptions(
                   { geometry::Vertex::getBindingDescription() })
            .withAttributeDescriptions(
                geometry::Vertex::getAttributeDescriptions());
    }

    VkPipelineVertexInputStateCreateInfo VertexInputBuilder::build()
    {
        VkPipelineVertexInputStateCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.vertexBindingDescriptionCount = _bindingDescriptions.size();
        createInfo.pVertexBindingDescriptions = _bindingDescriptions.data();
        createInfo.vertexAttributeDescriptionCount =
            _attributeDescriptions.size();
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
        const std::array<VkVertexInputAttributeDescription, 2>
            &attributeDescriptions)
    {
        _attributeDescriptions = attributeDescriptions;
        return *this;
    }
} // namespace brasio::renderer::vulkan::builders
