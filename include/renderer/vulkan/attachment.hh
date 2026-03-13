#pragma once

#include <vulkan/vulkan_core.h>

class Attachment
{
public:
    Attachment(const VkAttachmentDescription &description,
               const VkAttachmentReference &reference);

    const VkAttachmentDescription &getDescription() const;
    VkAttachmentDescription &getDescription();

    const VkAttachmentReference &getReference() const;
    VkAttachmentReference &getReference();

private:
    VkAttachmentDescription _description;
    VkAttachmentReference _reference;
};
