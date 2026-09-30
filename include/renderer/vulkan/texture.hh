#pragma once

#include <renderer/vulkan/image-attachment.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

#include <renderer/vulkan/texture-sampler.hh>
#include <images/p3-ppm.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class Texture : public ImageAttachment
    {
    public:
        Texture(const VulkanRenderer &renderer, const VkImageCreateInfo &imageInfo,
                VkImageViewCreateInfo imageViewInfo, images::P3PPM &textureImage);

        const images::P3PPM &getTextureImage() const;

        void createTextureSampler();

        TextureSamplerType &getTextureSampler();
        const TextureSamplerType &getTextureSampler() const;

    private:
        const images::P3PPM _textureImage;
        TextureSamplerType _textureSampler;
    };

    using TextureType = std::unique_ptr<Texture>;

} // namespace brasio::renderer::vulkan
