#include <renderer/vulkan/texture.hh>

#include <renderer/vulkan/memory.hh>
#include <renderer/vulkan/command-buffer.hh>
#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan
{

    Texture::Texture(const PhysicalDeviceType &physicalDevice,
                     const LogicalDeviceType &logicalDevice,
                     const VkImageCreateInfo &imageInfo,
                     const images::P3PPM &textureImage,
                     const VkMemoryPropertyFlags memoryProperties)
        : Handler("texture",
                  [&logicalDevice](const VkImage &image) {
                      vkDestroyImage(logicalDevice->getHandle(), image,
                                     nullptr);
                  })
        , _logicalDevice(logicalDevice)
        , _textureImage(textureImage)
        , _deviceMemory(nullptr)
    {
        BRASIO_LOG_TRACE("Creating texture", { "CREATE" });
        if (vkCreateImage(logicalDevice->getHandle(), &imageInfo, nullptr,
                          &getHandle())
            != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL("Could not create texture",
                                { "CREATE" });
        }
        BRASIO_LOG_TRACE("Created texture", { "CREATE" });
        _deviceMemory =
            std::make_unique<Memory>(physicalDevice, logicalDevice->getHandle(),
                                     *this, memoryProperties);
    }

    const images::P3PPM &Texture::getTextureImage() const
    {
        return _textureImage;
    }

    void Texture::transitionImageLayout(const VkCommandPool &commandPool,
                                        [[maybe_unused]] const VkFormat &format,
                                        const VkImageLayout &oldLayout,
                                        VkImageLayout &newLayout)
    {
        CommandBuffer commandBuffer(_logicalDevice, commandPool);

        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = oldLayout;
        barrier.newLayout = newLayout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = getHandle();
        barrier.subresourceRange = { .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                     .baseMipLevel = 0,
                                     .levelCount = 1,
                                     .baseArrayLayer = 0,
                                     .layerCount = 1 };
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = 0;

        vkCmdPipelineBarrier(commandBuffer.getHandle(), 0, 0, 0, 0, nullptr, 0,
                             nullptr, 1, &barrier);
    }

} // namespace brasio::renderer::vulkan
