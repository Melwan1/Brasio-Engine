#include <renderer/vulkan/builders/render-pass-builder.hh>

RenderPassBuilder::RenderPassBuilder(const VkDevice &logicalDevice)
    : _logicalDevice(logicalDevice)
{
    base();
}

RenderPassBuilder &RenderPassBuilder::base()
{
    _structureType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    _subpasses.clear();
    _dependencies.clear();
    _attachments.clear();
    return *this;
}

RenderPassType RenderPassBuilder::build()
{
    VkRenderPassCreateInfo createInfo{};
    createInfo.sType = _structureType;
    createInfo.attachmentCount = _attachmentDescriptions.size();
    createInfo.pAttachments = _attachmentDescriptions.data();
    createInfo.subpassCount = _subpasses.size();
    createInfo.pSubpasses = _subpasses.data();
    createInfo.dependencyCount = _dependencies.size();
    createInfo.pDependencies = _dependencies.data();
    return std::make_unique<RenderPass>(_logicalDevice, createInfo);
}

RenderPassBuilder &
RenderPassBuilder::withAdditionalSubpass(const VkSubpassDescription &subpass)
{
    _subpasses.emplace_back(subpass);
    return *this;
}

RenderPassBuilder &RenderPassBuilder::withAdditionalSubpassDependency(
    const VkSubpassDependency &dependency)
{
    _dependencies.emplace_back(dependency);
    return *this;
}

RenderPassBuilder &
RenderPassBuilder::withAdditionalAttachment(const Attachment &attachment)
{
    _attachments.emplace_back(attachment);
    _attachmentDescriptions.emplace_back(attachment.getDescription());
    return *this;
}
