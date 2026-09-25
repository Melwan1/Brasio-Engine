#include <renderer/vulkan/builders/depth-attachment-builder.hh>

namespace brasio::renderer::vulkan::builders
{

    DepthAttachmentBuilder::DepthAttachmentBuilder(
        const PhysicalDeviceType &physicalDevice,
        const LogicalDeviceType &logicalDevice)
        : _physicalDevice(physicalDevice)
        , _logicalDevice(logicalDevice)
    {
        base();
    }

    DepthAttachmentBuilder &DepthAttachmentBuilder::base()
    {
        return withExtent(0, 0).withFormat(VK_FORMAT_D24_UNORM_S8_UINT);
    }

    DepthAttachmentType DepthAttachmentBuilder::build()
    {
        VkImageCreateInfo imageInfo{};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent = { .width = _width, .height = _height, .depth = 1 };
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.format = _format;
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        imageInfo.samples = _sampleCount;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        VkImageViewCreateInfo imageViewInfo{};
        imageViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewInfo.format = _format;
        imageViewInfo.subresourceRange = { .aspectMask =
                                               VK_IMAGE_ASPECT_DEPTH_BIT,
                                           .baseMipLevel = 0,
                                           .levelCount = 1,
                                           .baseArrayLayer = 0,
                                           .layerCount = 1 };

        return std::make_unique<DepthAttachment>(
            _physicalDevice, _logicalDevice, imageInfo, imageViewInfo);
    }

    DepthAttachmentBuilder &DepthAttachmentBuilder::withWidth(uint32_t width)
    {
        _width = width;
        return *this;
    }

    DepthAttachmentBuilder &DepthAttachmentBuilder::withHeight(uint32_t height)
    {
        _height = height;
        return *this;
    }

    DepthAttachmentBuilder &DepthAttachmentBuilder::withExtent(uint32_t width,
                                                               uint32_t height)
    {
        return withWidth(width).withHeight(height);
    }

    DepthAttachmentBuilder &
    DepthAttachmentBuilder::withFormat(const VkFormat &format)
    {
        _format = format;
        return *this;
    }

    DepthAttachmentBuilder &DepthAttachmentBuilder::withSamples(
        const VkSampleCountFlagBits &sampleCount)
    {
        _sampleCount = sampleCount;
        return *this;
    }
} // namespace brasio::renderer::vulkan::builders
