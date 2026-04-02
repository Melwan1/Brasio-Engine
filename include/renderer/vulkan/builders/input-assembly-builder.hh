#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

#include <yaml-cpp/yaml.h>

namespace brasio::renderer::vulkan::builders
{
    class InputAssemblyBuilder
        : public core::Builder<VkPipelineInputAssemblyStateCreateInfo>
    {
    public:
        InputAssemblyBuilder();

        virtual InputAssemblyBuilder &base() override;
        virtual VkPipelineInputAssemblyStateCreateInfo build() override;

        InputAssemblyBuilder &
        withPrimitiveTopology(const VkPrimitiveTopology &topology);
        InputAssemblyBuilder &
        withPrimitiveRestartEnable(const VkBool32 &enabled);

        InputAssemblyBuilder &withConfig(const YAML::Node &config);

    private:
        VkStructureType _structureType;

        VkPrimitiveTopology _primitiveTopology;
        VkBool32 _primitiveRestartEnable;
    };
} // namespace brasio::renderer::vulkan::builders
