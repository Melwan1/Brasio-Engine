#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/texture.hh>
#include <images/p2-pgm.hh>
#include <images/p3-ppm.hh>

namespace brasio::renderer::vulkan::builders
{

    class TextureBuilder : public core::Builder<TextureType>
    {
    public:
        TextureBuilder(const VulkanRenderer &renderer);

        virtual TextureBuilder &base() override;
        virtual TextureType build() override;

        TextureBuilder &withWidth(uint32_t width);
        TextureBuilder &withHeight(uint32_t height);
        TextureBuilder &withImageType(const VkImageType &imageType);
        TextureBuilder &withFormat(const VkFormat &format);
        TextureBuilder &withTextureImage(const images::P2PGM &textureImage);
        TextureBuilder &withTextureImage(const images::P3PPM &textureImage);
        TextureBuilder &withUsage(const VkImageUsageFlags &usage);
        TextureBuilder &withSharingMode(const VkSharingMode &sharingMode);
        TextureBuilder &withTiling(const VkImageTiling &tiling);

    private:
        const VulkanRenderer &_renderer;
        VkStructureType _structureType;

        uint32_t _width;
        uint32_t _height;
        VkImageType _imageType;
        VkFormat _format;
        std::optional<images::P2PGM> _grayTextureImage;
        std::optional<images::P3PPM> _colorTextureImage;
        VkImageUsageFlags _usage;
        VkSharingMode _sharingMode;
        VkImageTiling _tiling;
    };
} // namespace brasio::renderer::vulkan::builders
