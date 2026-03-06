#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

class InputAssemblyBuilder
    : public Builder<VkPipelineInputAssemblyStateCreateInfo>
{
public:
    InputAssemblyBuilder();

    virtual InputAssemblyBuilder &base() override;
    virtual VkPipelineInputAssemblyStateCreateInfo build() override;

    InputAssemblyBuilder &
    withPrimitiveTopology(const VkPrimitiveTopology &topology);
    InputAssemblyBuilder &withPrimitiveRestartEnable(const VkBool32 &enabled);

private:
    VkStructureType _structureType;

    VkPrimitiveTopology _primitiveTopology;
    VkBool32 _primitiveRestartEnable;
};
