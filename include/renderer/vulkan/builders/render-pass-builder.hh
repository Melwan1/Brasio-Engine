#pragma once

#include <vector>

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/attachment.hh>
#include <renderer/vulkan/render-pass.hh>

namespace brasio::renderer::vulkan::builders
{
    class RenderPassBuilder : core::Builder<RenderPassType>
    {
    public:
        RenderPassBuilder(const VkDevice &device);

        virtual RenderPassBuilder &base() override;
        virtual RenderPassType build() override;

        RenderPassBuilder &
        withAdditionalSubpass(const VkSubpassDescription &subpass);
        RenderPassBuilder &
        withAdditionalSubpassDependency(const VkSubpassDependency &dependency);
        RenderPassBuilder &
        withAdditionalAttachment(const Attachment &attachment);

    private:
        VkDevice _logicalDevice;
        VkStructureType _structureType;
        std::vector<VkSubpassDescription> _subpasses;
        std::vector<VkSubpassDependency> _dependencies;
        std::vector<Attachment> _attachments;
        std::vector<VkAttachmentDescription> _attachmentDescriptions;
    };
} // namespace brasio::renderer::vulkan::builders
