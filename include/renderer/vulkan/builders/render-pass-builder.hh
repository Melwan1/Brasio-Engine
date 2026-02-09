#pragma once

#include <vector>

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/attachment.hh>

class RenderPassBuilder : Builder<VkRenderPassCreateInfo>
{
public:
    RenderPassBuilder();

    virtual RenderPassBuilder &base() override;
    virtual VkRenderPassCreateInfo build() override;

    RenderPassBuilder &
    withAdditionalSubpass(const VkSubpassDescription &subpass);
    RenderPassBuilder &
    withAdditionalSubpassDependency(const VkSubpassDependency &dependency);
    RenderPassBuilder &withAdditionalAttachment(const Attachment &attachment);

private:
    VkStructureType _structureType;
    std::vector<VkSubpassDescription> _subpasses;
    std::vector<VkSubpassDependency> _dependencies;
    std::vector<Attachment> _attachments;
    std::vector<VkAttachmentDescription> _attachmentDescriptions;
};
