#pragma once

#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan
{
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
} // namespace brasio::renderer::vulkan
