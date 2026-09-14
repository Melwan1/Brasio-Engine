#include <renderer/vulkan/texture.hh>

#include <renderer/vulkan/memory.hh>
#include <renderer/vulkan/command-buffer.hh>
#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/builders/buffer-builder.hh>

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
        , _textureImage(textureImage)
    {
        initMemory(physicalDevice, commandPool, textureImage.getSize(), textureImage.getData(), memoryProperties);
        createImageView();
    }

    const images::P3PPM &Texture::getTextureImage() const
    {
        return _textureImage;
    }

} // namespace brasio::renderer::vulkan
