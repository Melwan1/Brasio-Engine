#pragma once

#include <vector>

#include <vulkan/vulkan_core.h>

#include <core/builder.hh>

class DynamicStateBuilder : public Builder<VkPipelineDynamicStateCreateInfo>
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
