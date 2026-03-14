#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{
    class ViewportStateBuilder
        : public core::Builder<VkPipelineViewportStateCreateInfo>
    {
    public:
        ViewportStateBuilder();

        virtual ViewportStateBuilder &base() override;
        virtual VkPipelineViewportStateCreateInfo build() override;

        ViewportStateBuilder &withViewports(unsigned viewportCount);
        ViewportStateBuilder &withScissors(unsigned scissorCount);

    private:
        VkStructureType _structureType;

        unsigned _viewportCount;
        unsigned _scissorCount;
    };
} // namespace brasio::renderer::vulkan::builders
