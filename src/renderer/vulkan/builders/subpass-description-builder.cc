#include <renderer/vulkan/builders/subpass-description-builder.hh>
#include <renderer/vulkan/depth-attachment.hh>

namespace brasio::renderer::vulkan::builders
{
    SubpassDescriptionBuilder::SubpassDescriptionBuilder()
    {
        base();
    }

    SubpassDescriptionBuilder &SubpassDescriptionBuilder::base()
    {
        _bindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        return *this;
    }

    VkSubpassDescription SubpassDescriptionBuilder::build()
    {
        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = _bindPoint;
        subpass.colorAttachmentCount = _colorAttachmentReferences.size();
        subpass.pColorAttachments = _colorAttachmentReferences.data();
        if (_depthAttachmentDescription.has_value())
        {
            subpass.pDepthStencilAttachment = &(*_depthAttachmentReference);
        }
        subpass.pResolveAttachments = _resolveAttachmentReferences.data();
        return subpass;
    }

    SubpassDescriptionBuilder &
    SubpassDescriptionBuilder::withAdditionalAttachment(const ImageAttachment &attachment,
                                                        uint32_t attachmentId)
    {
        return withAdditionalAttachment(attachment.getAttachmentDescription(),
                                        attachment.getAttachmentReference(attachmentId));
    }

    SubpassDescriptionBuilder &SubpassDescriptionBuilder::withAdditionalAttachment(
        const VkAttachmentDescription &attachmentDescription,
        const VkAttachmentReference &attachmentReference)
    {
        if (attachmentDescription.finalLayout == VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL
            || attachmentDescription.finalLayout
                == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
        {
            _depthAttachmentDescription = attachmentDescription;
            _depthAttachmentReference = attachmentReference;
            return *this;
        }
        _colorAttachmentDescriptions.emplace_back(attachmentDescription);
        _colorAttachmentReferences.emplace_back(attachmentReference);
        return *this;
    }

    SubpassDescriptionBuilder &SubpassDescriptionBuilder::withAdditionalResolveAttachment(
        const VkAttachmentReference &attachmentReference)
    {
        _resolveAttachmentReferences.emplace_back(attachmentReference);
        return *this;
    }
} // namespace brasio::renderer::vulkan::builders
