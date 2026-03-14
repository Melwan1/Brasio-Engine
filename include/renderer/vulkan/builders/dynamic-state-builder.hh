#pragma once

#include <vector>

#include <vulkan/vulkan_core.h>

#include <core/builder.hh>

namespace brasio::renderer::vulkan::builders
{
    class DynamicStateBuilder
        : public core::Builder<VkPipelineDynamicStateCreateInfo>
    {
    public:
        DynamicStateBuilder();

        virtual VkPipelineDynamicStateCreateInfo build() override;
        virtual DynamicStateBuilder &base() override;

        DynamicStateBuilder &
        withDynamicStates(const std::vector<VkDynamicState> &dynamicStates);

    private:
        VkStructureType _structureType;
        std::vector<VkDynamicState> _dynamicStates;
    };
} // namespace brasio::renderer::vulkan::builders
