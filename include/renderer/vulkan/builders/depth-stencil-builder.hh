#pragma once

#include <core/builder.hh>
#include <vulkan/vulkan_core.h>
#include <yaml-cpp/yaml.h>

namespace brasio::renderer::vulkan::builders
{
    class DepthStencilBuilder : public core::Builder<VkPipelineDepthStencilStateCreateInfo>
    {
    public:
        DepthStencilBuilder();

        virtual DepthStencilBuilder &base() override;
        DepthStencilBuilder &withConfig(const YAML::Node &config);
        virtual VkPipelineDepthStencilStateCreateInfo build() override;

    private:
        VkStructureType _structureType;
        bool _depthTestEnable;
        bool _depthWriteEnable;
    };
} // namespace brasio::renderer::vulkan::builders
