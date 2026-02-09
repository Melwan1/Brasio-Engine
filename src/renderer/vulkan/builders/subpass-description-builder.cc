#include <renderer/vulkan/builders/subpass-description-builder.hh>

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
    subpass.colorAttachmentCount = _attachmentReferences.size();
    subpass.pColorAttachments = _attachmentReferences.data();
    return subpass;
}

SubpassDescriptionBuilder &SubpassDescriptionBuilder::withAdditionalAttachment(
    const VkAttachmentDescription &description,
    const VkAttachmentReference &reference)
{
    _attachments.emplace_back(description, reference);
    _attachmentReferences.emplace_back(reference);
    return *this;
}

SubpassDescriptionBuilder &SubpassDescriptionBuilder::withAdditionalAttachment(
    const Attachment &attachment)
{
    _attachments.emplace_back(attachment);
    _attachmentReferences.emplace_back(attachment.getReference());
    return *this;
}
