#pragma once

#include <vector>

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/image-attachment.hh>

namespace brasio::renderer::vulkan::builders
{
    class SubpassDescriptionBuilder : core::Builder<VkSubpassDescription>
    {
    public:
        SubpassDescriptionBuilder();

        virtual SubpassDescriptionBuilder &base() override;
        virtual VkSubpassDescription build() override;

        SubpassDescriptionBuilder &
        withAdditionalAttachment(const ImageAttachment &attachment,
                                 uint32_t attachmentId);

        SubpassDescriptionBuilder &withAdditionalAttachment(
            const VkAttachmentDescription &attachmentDescription,
            const VkAttachmentReference &attachmentReference);

    private:
        VkPipelineBindPoint _bindPoint;
        std::vector<VkAttachmentDescription> _colorAttachmentDescriptions;
        std::vector<VkAttachmentReference> _colorAttachmentReferences;
        std::optional<VkAttachmentDescription> _depthAttachmentDescription;
        std::optional<VkAttachmentReference> _depthAttachmentReference;
    };
} // namespace brasio::renderer::vulkan::builders
