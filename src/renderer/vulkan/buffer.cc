#include <renderer/vulkan/buffer.hh>

#include <cstring>

#include <renderer/vulkan/memory.hh>
#include <renderer/vulkan/texture.hh>
#include <renderer/vulkan/command-buffer.hh>

namespace brasio::renderer::vulkan
{
    Buffer::Buffer(const PhysicalDeviceType &physicalDevice,
                   const LogicalDeviceType &logicalDevice,
                   const VkBufferCreateInfo &createInfo,
                   const VkMemoryPropertyFlags memoryProperties, void *data)
        : Handler("buffer",
                  [&logicalDevice](const VkBuffer &buffer) {
                      vkDestroyBuffer(logicalDevice->getHandle(), buffer,
                                      nullptr);
                  })
        , _logicalDevice(logicalDevice)
        , _deviceMemory(nullptr)
    {
        BRASIO_LOG_TRACE("Creating buffer", { "CREATE" });
        if (vkCreateBuffer(logicalDevice->getHandle(), &createInfo, nullptr,
                           &getHandle())
            != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL("Could not create buffer",
                                { "CREATE" });
        }
        BRASIO_LOG_TRACE("Created buffer", { "CREATE" });
        _deviceMemory = std::make_unique<Memory>(
            physicalDevice, logicalDevice->getHandle(), *this, memoryProperties,
            data, createInfo.size);
    }

    void Buffer::copyInto(const Buffer &other, VkCommandPool commandPool,
                          VkDeviceSize size)
    {
        CommandBuffer commandBuffer(_logicalDevice, commandPool);

        VkBufferCopy copyRegion{};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer.getHandle(), getHandle(),
                        other.getHandle(), 1, &copyRegion);
    }

    void Buffer::copyInto(const Texture &other, VkCommandPool commandPool)
    {
        CommandBuffer commandBuffer(_logicalDevice, commandPool);

        VkBufferImageCopy region{};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;

        region.imageSubresource = { .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                    .mipLevel = 0,
                                    .baseArrayLayer = 0,
                                    .layerCount = 1 };
        region.imageOffset = { 0, 0, 0 };
        region.imageExtent = {
            static_cast<uint32_t>(other.getTextureImage().getWidth()),
            static_cast<uint32_t>(other.getTextureImage().getHeight()), 1
        };

        vkCmdCopyBufferToImage(
            commandBuffer.getHandle(), getHandle(), other.getHandle(),
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
    }

    void Buffer::mapMemory()
    {
        _deviceMemory->map();
    }

    void Buffer::unmapMemory()
    {
        _deviceMemory->unmap();
    }

    void Buffer::setContent(void *content)
    {
        _deviceMemory->setContent(content);
    }
} // namespace brasio::renderer::vulkan
