#include <renderer/vulkan/texture.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

#include <renderer/vulkan/memory.hh>
#include <renderer/vulkan/command-buffer.hh>

#include <renderer/vulkan/builders/texture-sampler-builder.hh>

namespace brasio::renderer::vulkan
{

    Texture::Texture(const VulkanRenderer &renderer, const VkImageCreateInfo &imageInfo,
                     VkImageViewCreateInfo imageViewInfo, images::P3PPM &textureImage)
        : ImageAttachment(renderer, imageInfo, imageViewInfo)
        , _colorTextureImage(textureImage)
    {
        initMemory(textureImage.getSize(), textureImage.getData());
        createImageView();
        createTextureSampler();
    }

    Texture::Texture(const VulkanRenderer &renderer, const VkImageCreateInfo &imageInfo,
                     VkImageViewCreateInfo imageViewInfo, images::P2PGM &textureImage)
        : ImageAttachment(renderer, imageInfo, imageViewInfo)
        , _grayTextureImage(textureImage)
    {
        initMemory(textureImage.getSize(), textureImage.getData());
        createImageView();
        createTextureSampler();
    }

    const images::P2PGM &Texture::getGrayTextureImage() const
    {
        return _grayTextureImage.value();
    }

    const images::P3PPM &Texture::getColorTextureImage() const
    {
        return _colorTextureImage.value();
    }

    void Texture::createTextureSampler()
    {
        _textureSampler = builders::TextureSamplerBuilder(_renderer).build();
    }

    TextureSamplerType &Texture::getTextureSampler()
    {
        return _textureSampler;
    }

    const TextureSamplerType &Texture::getTextureSampler() const
    {
        return _textureSampler;
    }

} // namespace brasio::renderer::vulkan
