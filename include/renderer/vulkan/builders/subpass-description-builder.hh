#pragma once

#include <vector>

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/attachment.hh>

namespace brasio::renderer::vulkan::builders
{
    class SubpassDescriptionBuilder : core::Builder<VkSubpassDescription>
    {
    public:
        SubpassDescriptionBuilder();

        virtual SubpassDescriptionBuilder &base() override;
        virtual VkSubpassDescription build() override;

        SubpassDescriptionBuilder &
        withAdditionalAttachment(const VkAttachmentDescription &description,
                                 const VkAttachmentReference &reference);

        SubpassDescriptionBuilder &
        withAdditionalAttachment(const Attachment &attachment);

        const Attachment &at(uint32_t index) const;
        Attachment &at(uint32_t index);

    private:
        VkPipelineBindPoint _bindPoint;
        std::vector<Attachment> _attachments;
        std::vector<VkAttachmentReference> _attachmentReferences;
    };
} // namespace brasio::renderer::vulkan::builders
