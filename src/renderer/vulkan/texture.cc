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
                     images::P3PPM &textureImage,
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

        builders::BufferBuilder stagingBuilder(physicalDevice, logicalDevice);
        BufferType stagingBuffer = stagingBuilder.withSize(textureImage.getSize()).withData(textureImage.getData()).withUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT).withMemoryProperties(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT).build();
        //stagingBuffer->unmapMemory();

        transitionImageLayout(commandPool, imageInfo.format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        stagingBuffer->copyInto(*this, commandPool);
        transitionImageLayout(commandPool, imageInfo.format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    }

    const images::P3PPM &Texture::getTextureImage() const
    {
        return _textureImage;
    }

    void Texture::transitionImageLayout(const VkCommandPool &commandPool,
                                        [[maybe_unused]] const VkFormat &format,
                                        const VkImageLayout &oldLayout,
                                        const VkImageLayout &newLayout)
    {
        CommandBuffer commandBuffer(_logicalDevice, commandPool);

        VkPipelineStageFlags sourceStage;
        VkPipelineStageFlags destinationStage;

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
        if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
        {
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        }
        else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
            sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        }
        else {
            BRASIO_LOG_ERROR("Unsupported layout transition", { "CREATE", "TEXTURE" });
        }

        vkCmdPipelineBarrier(commandBuffer.getHandle(), sourceStage, destinationStage, 0, 0, nullptr, 0,
                             nullptr, 1, &barrier);
    }

} // namespace brasio::renderer::vulkan
