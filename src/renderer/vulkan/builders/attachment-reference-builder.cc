#include <renderer/vulkan/builders/attachment-reference-builder.hh>

AttachmentReferenceBuilder::AttachmentReferenceBuilder()
{
    base();
}

AttachmentReferenceBuilder &AttachmentReferenceBuilder::base()
{
    _index = 0;
    _layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    return *this;
}

VkAttachmentReference AttachmentReferenceBuilder::build()
{
    VkAttachmentReference attachmentReference{};
    attachmentReference.attachment = _index;
    attachmentReference.layout = _layout;
    return attachmentReference;
}
