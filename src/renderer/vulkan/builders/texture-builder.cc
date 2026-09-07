#include <renderer/vulkan/builders/texture-builder.hh>
#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{

    TextureBuilder::TextureBuilder(const PhysicalDeviceType &physicalDevice,
                                   const LogicalDeviceType &logicalDevice)
        : _physicalDevice(physicalDevice)
        , _logicalDevice(logicalDevice)
        , _textureImage(images::P3PPM::empty())
    {
        base();
    }

    TextureBuilder &TextureBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        return withImageType(VK_IMAGE_TYPE_2D)
            .withSharingMode(VK_SHARING_MODE_EXCLUSIVE)
            .withUsage(VK_IMAGE_USAGE_TRANSFER_DST_BIT
                       | VK_IMAGE_USAGE_SAMPLED_BIT)
            .withMemoryProperties(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
            .withTiling(VK_IMAGE_TILING_OPTIMAL);
    }

    TextureType TextureBuilder::build()
    {
        VkImageCreateInfo imageInfo{};
        imageInfo.sType = _structureType;
        imageInfo.imageType = _imageType;
        imageInfo.extent = { .width = _width, .height = _height, .depth = 1 };
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.format = _format;
        imageInfo.tiling = _tiling;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = _usage;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.sharingMode = _sharingMode;

        return std::make_unique<Texture>(_physicalDevice, _logicalDevice, _commandPool,
                                         imageInfo, _textureImage,
                                         _memoryProperties);
    }

    TextureBuilder &TextureBuilder::withWidth(uint32_t width)
    {
        _width = width;
        return *this;
    }

    TextureBuilder &TextureBuilder::withHeight(uint32_t height)
    {
        _height = height;
        return *this;
    }

    TextureBuilder &TextureBuilder::withImageType(const VkImageType &imageType)
    {
        _imageType = imageType;
        return *this;
    }

    TextureBuilder &TextureBuilder::withFormat(const VkFormat &format)
    {
        _format = format;
        return *this;
    }

    TextureBuilder &
    TextureBuilder::withTextureImage(const images::P3PPM &textureImage)
    {
        _textureImage = textureImage;
        return withWidth(textureImage.getWidth())
            .withHeight(textureImage.getHeight())
            .withImageType(VK_IMAGE_TYPE_2D)
            .withFormat(VK_FORMAT_R8G8B8A8_SRGB);
    }

    TextureBuilder &TextureBuilder::withUsage(const VkImageUsageFlags &usage)
    {
        _usage = usage;
        return *this;
    }

    TextureBuilder &
    TextureBuilder::withSharingMode(const VkSharingMode &sharingMode)
    {
        _sharingMode = sharingMode;
        return *this;
    }

    TextureBuilder &TextureBuilder::withMemoryProperties(
        const VkMemoryPropertyFlags &memoryProperties)
    {
        _memoryProperties = memoryProperties;
        return *this;
    }

    TextureBuilder &TextureBuilder::withTiling(const VkImageTiling &tiling)
    {
        _tiling = tiling;
        return *this;
    }

    TextureBuilder &TextureBuilder::withCommandPool(const VkCommandPool &commandPool)
    {
        _commandPool = commandPool;
        return *this;
    }
} // namespace brasio::renderer::vulkan::builders
