#include <renderer/vulkan/texture.hh>

#include <renderer/vulkan/memory.hh>
#include <renderer/vulkan/command-buffer.hh>

#include <renderer/vulkan/builders/texture-sampler-builder.hh>

namespace brasio::renderer::vulkan
{

    Texture::Texture(const PhysicalDeviceType &physicalDevice,
                     const LogicalDeviceType &logicalDevice,
                     const VkCommandPool &commandPool,
                     const VkImageCreateInfo &imageInfo,
                     VkImageViewCreateInfo imageViewInfo,
                     images::P3PPM &textureImage,
                     const VkMemoryPropertyFlags memoryProperties)
        : ImageAttachment(logicalDevice, imageInfo, imageViewInfo)
        , _physicalDevice(physicalDevice)
        , _logicalDevice(logicalDevice)
        , _textureImage(textureImage)
    {
        initMemory(_physicalDevice, commandPool, textureImage.getSize(), textureImage.getData(), memoryProperties);
        createImageView();
        createTextureSampler();
    }

    const images::P3PPM &Texture::getTextureImage() const
    {
        return _textureImage;
    }

    void Texture::createTextureSampler()
    {
        _textureSampler = builders::TextureSamplerBuilder(_physicalDevice, _logicalDevice).build();
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
