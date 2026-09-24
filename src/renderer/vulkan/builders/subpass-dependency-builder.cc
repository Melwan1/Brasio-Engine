#include <renderer/vulkan/builders/subpass-dependency-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    SubpassDependencyBuilder::SubpassDependencyBuilder()
    {
        base();
    }

    SubpassDependencyBuilder &SubpassDependencyBuilder::base()
    {
        _srcSubpass = VK_SUBPASS_EXTERNAL;
        _dstSubpass = 0;
        return withSrcStageMask(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT)
            .withSrcAccessMask(0)
            .withDstStageMask(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT)
            .withDstAccessMask(VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT);
    }

    VkSubpassDependency SubpassDependencyBuilder::build()
    {
        VkSubpassDependency dependency{};
        dependency.srcSubpass = _srcSubpass;
        dependency.dstSubpass = _dstSubpass;
        dependency.srcStageMask = _srcStageMask;
        dependency.srcAccessMask = _srcAccessMask;
        dependency.dstStageMask = _dstStageMask;
        dependency.dstAccessMask = _dstAccessMask;
        return dependency;
    }

    SubpassDependencyBuilder &SubpassDependencyBuilder::withSrcStageMask(
        const VkPipelineStageFlags &srcStageMask)
    {
        _srcStageMask = srcStageMask;
        return *this;
    }

    SubpassDependencyBuilder &SubpassDependencyBuilder::withSrcAccessMask(
        const VkAccessFlags &srcAccessMask)
    {
        _srcAccessMask = srcAccessMask;
        return *this;
    }

    SubpassDependencyBuilder &SubpassDependencyBuilder::withDstStageMask(
        const VkPipelineStageFlags &dstStageMask)
    {
        _dstStageMask = dstStageMask;
        return *this;
    }

    SubpassDependencyBuilder &SubpassDependencyBuilder::withDstAccessMask(
        const VkAccessFlags &dstAccessMask)
    {
        _dstAccessMask = dstAccessMask;
        return *this;
    }
} // namespace brasio::renderer::vulkan::builders
