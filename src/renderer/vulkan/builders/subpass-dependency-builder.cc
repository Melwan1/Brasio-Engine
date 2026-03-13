#include <renderer/vulkan/builders/subpass-dependency-builder.hh>

SubpassDependencyBuilder::SubpassDependencyBuilder()
{
    base();
}

SubpassDependencyBuilder &SubpassDependencyBuilder::base()
{
    _srcSubpass = VK_SUBPASS_EXTERNAL;
    _dstSubpass = 0;
    _srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    _srcAccessMask = 0;
    _dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    _dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    return *this;
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
