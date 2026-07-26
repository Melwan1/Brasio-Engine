#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/memory.hh>
#include <images/p3-ppm.hh>

namespace brasio::renderer::vulkan
{

    class Texture : public core::Handler<VkImage>
    {
    public:
        Texture(const PhysicalDeviceType &physicalDevice,
                const LogicalDeviceType &logicalDevice,
                const VkImageCreateInfo &imageInfo,
                const images::P3PPM &textureImage,
                const VkMemoryPropertyFlags memoryProperties);

        const images::P3PPM &getTextureImage() const;

        void transitionImageLayout(const VkCommandPool &commandPool,
                                   [[maybe_unused]] const VkFormat &format,
                                   const VkImageLayout &oldLayout,
                                   VkImageLayout &newLayout);

    private:
        const LogicalDeviceType &_logicalDevice;
        const images::P3PPM _textureImage;
        MemoryType _deviceMemory;
    };

    using TextureType = std::unique_ptr<Texture>;

} // namespace brasio::renderer::vulkan
