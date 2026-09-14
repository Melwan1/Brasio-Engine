#pragma once

#include <renderer/vulkan/image-attachment.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

#include <renderer/vulkan/logical-device.hh>
#include <images/p3-ppm.hh>

namespace brasio::renderer::vulkan
{

    class Texture : public ImageAttachment
    {
    public:
        Texture(const PhysicalDeviceType &physicalDevice,
                const LogicalDeviceType &logicalDevice,
                const VkCommandPool &commandPool,
                const VkImageCreateInfo &imageInfo,
                VkImageViewCreateInfo imageViewInfo,
                images::P3PPM &textureImage,
                const VkMemoryPropertyFlags memoryProperties);

        const images::P3PPM &getTextureImage() const;

    private:
        const images::P3PPM _textureImage;
    };

    using TextureType = std::unique_ptr<Texture>;

} // namespace brasio::renderer::vulkan
