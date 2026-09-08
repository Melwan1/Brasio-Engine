#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/texture.hh>
#include <images/p3-ppm.hh>

namespace brasio::renderer::vulkan::builders
{

    class TextureBuilder : public core::Builder<TextureType>
    {
    public:
        TextureBuilder(const PhysicalDeviceType &physicalDevice,
                       const LogicalDeviceType &logicalDevice);

        virtual TextureBuilder &base() override;
        virtual TextureType build() override;

        TextureBuilder &withWidth(uint32_t width);
        TextureBuilder &withHeight(uint32_t height);
        TextureBuilder &withImageType(const VkImageType &imageType);
        TextureBuilder &withFormat(const VkFormat &format);
        TextureBuilder &withTextureImage(const images::P3PPM &textureImage);
        TextureBuilder &withUsage(const VkImageUsageFlags &usage);
        TextureBuilder &withSharingMode(const VkSharingMode &sharingMode);
        TextureBuilder &
        withMemoryProperties(const VkMemoryPropertyFlags &memoryProperties);
        TextureBuilder &withTiling(const VkImageTiling &tiling);

        TextureBuilder &withCommandPool(const VkCommandPool &commandPool);

    private:
        const PhysicalDeviceType &_physicalDevice;
        const LogicalDeviceType &_logicalDevice;
        VkStructureType _structureType;

        uint32_t _width;
        uint32_t _height;
        VkImageType _imageType;
        VkFormat _format;
        images::P3PPM _textureImage;
        VkImageUsageFlags _usage;
        VkSharingMode _sharingMode;
        VkMemoryPropertyFlags _memoryProperties;
        VkImageTiling _tiling;

        VkCommandPool _commandPool;
    };
} // namespace brasio::renderer::vulkan::builders
