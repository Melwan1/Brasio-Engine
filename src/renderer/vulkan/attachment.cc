#include <renderer/vulkan/attachment.hh>

Attachment::Attachment(const VkAttachmentDescription &description,
                       const VkAttachmentReference &reference)
    : _description(description)
    , _reference(reference)
{}

const VkAttachmentDescription &Attachment::getDescription() const
{
    return _description;
}

VkAttachmentDescription &Attachment::getDescription()
{
    return _description;
}

const VkAttachmentReference &Attachment::getReference() const
{
    return _reference;
}

VkAttachmentReference &Attachment::getReference()
{
    return _reference;
}
