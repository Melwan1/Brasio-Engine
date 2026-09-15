#include <renderer/vulkan/builders/depth-stencil-builder.hh>

namespace brasio::renderer::vulkan::builders
{

    DepthStencilBuilder::DepthStencilBuilder()
    {
        base();
    }

    DepthStencilBuilder &DepthStencilBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        return *this;
    }

    VkPipelineDepthStencilStateCreateInfo DepthStencilBuilder::build()
    {
        VkPipelineDepthStencilStateCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.depthTestEnable = VK_TRUE;
        createInfo.depthWriteEnable = VK_TRUE;
        createInfo.depthCompareOp = VK_COMPARE_OP_LESS;
        createInfo.depthBoundsTestEnable = VK_FALSE;
        createInfo.minDepthBounds = 0.0f;
        createInfo.maxDepthBounds = 0.0f;
        createInfo.stencilTestEnable = VK_FALSE;
        createInfo.front = {};
        createInfo.back = {};

        return createInfo;
    }
}
