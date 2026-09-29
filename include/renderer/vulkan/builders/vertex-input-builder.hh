#pragma once

#include <array>

#include <vulkan/vulkan_core.h>

#include <core/builder.hh>
#include <geometry/vertex.hh>

namespace brasio::renderer::vulkan::builders
{
    class VertexInputBuilder : public core::Builder<VkPipelineVertexInputStateCreateInfo>
    {
    public:
        VertexInputBuilder();

        virtual VertexInputBuilder &base() override;
        virtual VkPipelineVertexInputStateCreateInfo build() override;

        VertexInputBuilder &withBindingDescriptions(
            const std::vector<VkVertexInputBindingDescription> &bindingDescriptions);

        VertexInputBuilder &withAttributeDescriptions(
            const std::vector<VkVertexInputAttributeDescription> &attributeDescriptions);

        VertexInputBuilder &withParticleInput();

    private:
        VkStructureType _structureType;
        std::vector<VkVertexInputBindingDescription> _bindingDescriptions;
        std::vector<VkVertexInputAttributeDescription> _attributeDescriptions;
    };
} // namespace brasio::renderer::vulkan::builders
