#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

class ViewportStateBuilder : public Builder<VkPipelineViewportStateCreateInfo>
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
