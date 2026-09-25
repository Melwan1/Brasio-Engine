#include <renderer/vulkan/depth-attachment.hh>

namespace brasio::renderer::vulkan
{

    DepthAttachment::DepthAttachment(const PhysicalDeviceType &physicalDevice,
                                     const LogicalDeviceType &logicalDevice,
                                     const VkImageCreateInfo &imageInfo,
                                     const VkImageViewCreateInfo &imageViewInfo)
        : ImageAttachment(logicalDevice, imageInfo, imageViewInfo)
    {
        initMemory(physicalDevice, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        createImageView();
    }

    VkAttachmentDescription DepthAttachment::getAttachmentDescription() const
    {
        VkAttachmentDescription attachmentDescription = ImageAttachment::getAttachmentDescription();
        attachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachmentDescription.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        return attachmentDescription;
    }

    VkAttachmentReference DepthAttachment::getAttachmentReference(uint32_t attachmentId) const
    {
        VkAttachmentReference attachmentReference =
            ImageAttachment::getAttachmentReference(attachmentId);
        attachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        return attachmentReference;
    }

} // namespace brasio::renderer::vulkan
