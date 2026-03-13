#include <renderer/vulkan/builders/color-blend-state-builder.hh>
#include <vulkan/vulkan_core.h>

ColorBlendStateBuilder::ColorBlendStateBuilder()
{
    base();
}

ColorBlendStateBuilder &ColorBlendStateBuilder::base()
{
    _structureType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    _colorBlendAttachments.clear();
    return withLogicOpEnable(VK_FALSE).withLogicOp(VK_LOGIC_OP_COPY);
}

ColorBlendStateBuilder &
ColorBlendStateBuilder::withLogicOpEnable(const VkBool32 &logicOpEnable)
{
    _logicOpEnable = logicOpEnable;
    return *this;
}

ColorBlendStateBuilder &
ColorBlendStateBuilder::withLogicOp(const VkLogicOp &logicOp)
{
    _logicOp = logicOp;
    return *this;
}

ColorBlendStateBuilder &ColorBlendStateBuilder::withColorBlendAttachments(
    const std::vector<VkPipelineColorBlendAttachmentState>
        &colorBlendAttachments)
{
    _colorBlendAttachments = colorBlendAttachments;
    return *this;
}

VkPipelineColorBlendStateCreateInfo ColorBlendStateBuilder::build()
{
    VkPipelineColorBlendStateCreateInfo createInfo{};
    createInfo.sType = _structureType;
    createInfo.logicOpEnable = _logicOpEnable;
    createInfo.logicOp = _logicOp;
    createInfo.attachmentCount = _colorBlendAttachments.size();
    createInfo.pAttachments = _colorBlendAttachments.data();
    for (unsigned i = 0; i < 4; i++)
    {
        createInfo.blendConstants[i] = 0.0f;
    }
    return createInfo;
}
