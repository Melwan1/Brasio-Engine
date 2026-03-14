#include <renderer/vulkan/builders/image-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    ImageBuilder::ImageBuilder(const VkDevice &logicalDevice,
                               const VkImage &image, const VkFormat &format)
        : _logicalDevice(logicalDevice)
        , _image(image)
        , _format(format)
    {
        base();
    }

    ImageBuilder &ImageBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        _imageViewType = VK_IMAGE_VIEW_TYPE_2D;
        _componentMapping.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        _componentMapping.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        _componentMapping.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        _componentMapping.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        _aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        _baseMipLevel = 0;
        _levelCount = 1;
        _baseArrayLayer = 0;
        _layerCount = 1;

        return *this;
    }

    ImageType ImageBuilder::build()
    {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = _image;
        createInfo.viewType = _imageViewType;
        createInfo.format = _format;
        createInfo.components = _componentMapping;
        createInfo.subresourceRange.aspectMask = _aspectMask;
        createInfo.subresourceRange.baseArrayLayer = _baseArrayLayer;
        createInfo.subresourceRange.baseMipLevel = _baseMipLevel;
        createInfo.subresourceRange.layerCount = _layerCount;
        createInfo.subresourceRange.levelCount = _levelCount;

        return std::make_unique<Image>(_logicalDevice, _image, createInfo);
    }
} // namespace brasio::renderer::vulkan::builders
