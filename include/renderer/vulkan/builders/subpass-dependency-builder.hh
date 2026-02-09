#pragma once

#include <vulkan/vulkan_core.h>

#include <core/builder.hh>

class SubpassDependencyBuilder : public Builder<VkSubpassDependency>
{
public:
    SubpassDependencyBuilder();

    virtual SubpassDependencyBuilder &base() override;
    virtual VkSubpassDependency build() override;

private:
    uint32_t _srcSubpass;
    uint32_t _dstSubpass;

    VkPipelineStageFlags _srcStageMask;
    VkAccessFlags _srcAccessMask;

    VkPipelineStageFlags _dstStageMask;
    VkAccessFlags _dstAccessMask;
};
