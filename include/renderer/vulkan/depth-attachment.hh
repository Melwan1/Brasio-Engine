#pragma once

#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/physical-device.hh>
#include <renderer/vulkan/image-attachment.hh>

namespace brasio::renderer::vulkan
{

    class DepthAttachment : public ImageAttachment
    {
    public:
        DepthAttachment(const PhysicalDeviceType &physicalDevice,
                        const LogicalDeviceType &logicalDevice,
                        const VkImageCreateInfo &imageInfo,
                        const VkImageViewCreateInfo &imageViewInfo);

        VkAttachmentDescription getAttachmentDescription() const override;
        VkAttachmentReference
        getAttachmentReference(uint32_t attachmentId) const override;
    };

    using DepthAttachmentType = std::unique_ptr<DepthAttachment>;
} // namespace brasio::renderer::vulkan
