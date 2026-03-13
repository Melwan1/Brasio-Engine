#include <renderer/vulkan/builders/color-blend-attachment-builder.hh>
#include <vulkan/vulkan_core.h>

ColorBlendAttachmentBuilder::ColorBlendAttachmentBuilder()
{
    base();
}

ColorBlendAttachmentBuilder &ColorBlendAttachmentBuilder::base()
{
    return withColorWriteMask(
               VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT
               | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT)
        .withBlendEnable(VK_FALSE)
        .withSrcColorBlendFactor(VK_BLEND_FACTOR_ONE)
        .withDstColorBlendFactor(VK_BLEND_FACTOR_ZERO)
        .withColorBlendOp(VK_BLEND_OP_ADD)
        .withSrcAlphaBlendFactor(VK_BLEND_FACTOR_ONE)
        .withDstAlphaBlendFactor(VK_BLEND_FACTOR_ZERO)
        .withAlphaBlendOp(VK_BLEND_OP_ADD);
}

ColorBlendAttachmentBuilder &ColorBlendAttachmentBuilder::withColorWriteMask(
    const VkColorComponentFlags &colorWriteMask)
{
    _colorWriteMask = colorWriteMask;
    return *this;
}

ColorBlendAttachmentBuilder &
ColorBlendAttachmentBuilder::withBlendEnable(const VkBool32 &blendEnable)
{
    _blendEnable = blendEnable;
    return *this;
}

ColorBlendAttachmentBuilder &
ColorBlendAttachmentBuilder::withSrcColorBlendFactor(
    const VkBlendFactor &srcColorBlendFactor)
{
    _srcColorBlendFactor = srcColorBlendFactor;
    return *this;
}

ColorBlendAttachmentBuilder &
ColorBlendAttachmentBuilder::withDstColorBlendFactor(
    const VkBlendFactor &dstColorBlendFactor)
{
    _dstColorBlendFactor = dstColorBlendFactor;
    return *this;
}

ColorBlendAttachmentBuilder &
ColorBlendAttachmentBuilder::withColorBlendOp(const VkBlendOp &colorBlendOp)
{
    _colorBlendOp = colorBlendOp;
    return *this;
}

ColorBlendAttachmentBuilder &
ColorBlendAttachmentBuilder::withSrcAlphaBlendFactor(
    const VkBlendFactor &srcAlphaBlendFactor)
{
    _srcAlphaBlendFactor = srcAlphaBlendFactor;
    return *this;
}

ColorBlendAttachmentBuilder &
ColorBlendAttachmentBuilder::withDstAlphaBlendFactor(
    const VkBlendFactor &dstAlphaBlendFactor)
{
    _dstAlphaBlendFactor = dstAlphaBlendFactor;
    return *this;
}

ColorBlendAttachmentBuilder &
ColorBlendAttachmentBuilder::withAlphaBlendOp(const VkBlendOp &alphaBlendOp)
{
    _alphaBlendOp = alphaBlendOp;
    return *this;
}

VkPipelineColorBlendAttachmentState ColorBlendAttachmentBuilder::build()
{
    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = _colorWriteMask;
    colorBlendAttachment.blendEnable = _blendEnable;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
    return colorBlendAttachment;
}
