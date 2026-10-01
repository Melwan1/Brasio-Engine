#pragma once

#include <renderer/vulkan/image-attachment.hh>

#include <vulkan/vulkan_core.h>

#include <memory>
#include <optional>

#include <renderer/vulkan/texture-sampler.hh>
#include <images/p2-pgm.hh>
#include <images/p3-ppm.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class Texture : public ImageAttachment
    {
    public:
        Texture(const VulkanRenderer &renderer, const VkImageCreateInfo &imageInfo,
                VkImageViewCreateInfo imageViewInfo, images::P3PPM &textureImage);

        // only used for font rendering
        Texture(const VulkanRenderer &renderer, const VkImageCreateInfo &imageInfo,
                VkImageViewCreateInfo imageViewInfo, images::P2PGM &textureImage);

        const images::P2PGM &getGrayTextureImage() const;
        const images::P3PPM &getColorTextureImage() const;

        void createTextureSampler();

        TextureSamplerType &getTextureSampler();
        const TextureSamplerType &getTextureSampler() const;

    private:
        std::optional<const images::P2PGM> _grayTextureImage;
        std::optional<const images::P3PPM> _colorTextureImage;
        TextureSamplerType _textureSampler;
    };

    using TextureType = std::unique_ptr<Texture>;

} // namespace brasio::renderer::vulkan
