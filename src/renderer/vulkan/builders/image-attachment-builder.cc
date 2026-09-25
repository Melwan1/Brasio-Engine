#include <renderer/vulkan/builders/image-attachment-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    ImageAttachmentBuilder::ImageAttachmentBuilder(
        const PhysicalDeviceType &physicalDevice,
        const LogicalDeviceType &logicalDevice)
        : _physicalDevice(physicalDevice)
        , _logicalDevice(logicalDevice)
    {
        base();
    }

    ImageAttachmentBuilder &ImageAttachmentBuilder::base()
    {
        return withImageType(VK_IMAGE_TYPE_2D)
            .withSharingMode(VK_SHARING_MODE_EXCLUSIVE)
            .withUsage(VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT
                       | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
            .withMemoryProperties(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
            .withTiling(VK_IMAGE_TILING_OPTIMAL);
    }

    ImageAttachmentBuilder &ImageAttachmentBuilder::withWidth(uint32_t width)
    {
        _width = width;
        return *this;
    }

    ImageAttachmentBuilder &ImageAttachmentBuilder::withHeight(uint32_t height)
    {
        _height = height;
        return *this;
    }

    ImageAttachmentBuilder &ImageAttachmentBuilder::withExtent(uint32_t width,
                                                               uint32_t height)
    {
        return withWidth(width).withHeight(height);
    }

    ImageAttachmentBuilder &
    ImageAttachmentBuilder::withImageType(const VkImageType &imageType)
    {
        _imageType = imageType;
        return *this;
    }

    ImageAttachmentBuilder &
    ImageAttachmentBuilder::withFormat(const VkFormat &format)
    {
        _format = format;
        return *this;
    }

    ImageAttachmentBuilder &
    ImageAttachmentBuilder::withUsage(const VkImageUsageFlags &usage)
    {
        _usage = usage;
        return *this;
    }

    ImageAttachmentBuilder &
    ImageAttachmentBuilder::withSharingMode(const VkSharingMode &sharingMode)
    {
        _sharingMode = sharingMode;
        return *this;
    }

    ImageAttachmentBuilder &ImageAttachmentBuilder::withMemoryProperties(
        const VkMemoryPropertyFlags &memoryProperties)
    {
        _memoryProperties = memoryProperties;
        return *this;
    }

    ImageAttachmentBuilder &
    ImageAttachmentBuilder::withTiling(const VkImageTiling &tiling)
    {
        _tiling = tiling;
        return *this;
    }

    ImageAttachmentBuilder &ImageAttachmentBuilder::withSamples(
        const VkSampleCountFlagBits &sampleCount)
    {
        _sampleCount = sampleCount;
        return *this;
    }

    ImageAttachmentType ImageAttachmentBuilder::build()
    {
        VkImageCreateInfo imageCreateInfo{};
        imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageCreateInfo.imageType = _imageType;
        imageCreateInfo.extent = { _width, _height, 1 };
        imageCreateInfo.mipLevels = 1;
        imageCreateInfo.arrayLayers = 1;
        imageCreateInfo.format = _format;
        imageCreateInfo.tiling = _tiling;
        imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageCreateInfo.usage = _usage;
        imageCreateInfo.samples = _sampleCount;
        imageCreateInfo.sharingMode = _sharingMode;

        VkImageViewCreateInfo imageViewCreateInfo{};
        imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCreateInfo.image =
            VK_NULL_HANDLE; // created in the image attachment constructor
        imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCreateInfo.format = _format;
        imageViewCreateInfo.subresourceRange = { .aspectMask =
                                                     VK_IMAGE_ASPECT_COLOR_BIT,
                                                 .baseMipLevel = 0,
                                                 .levelCount = 1,
                                                 .baseArrayLayer = 0,
                                                 .layerCount = 1 };

        ImageAttachmentType imageAttachment = std::make_unique<ImageAttachment>(
            _logicalDevice, imageCreateInfo, imageViewCreateInfo);
        imageAttachment->initMemory(_physicalDevice, _memoryProperties);
        imageAttachment->createImageView();
        return imageAttachment;
    }
} // namespace brasio::renderer::vulkan::builders
