#include <renderer/vulkan/buffer.hh>

#include <renderer/vulkan/memory.hh>
#include <renderer/vulkan/texture.hh>
#include <renderer/vulkan/command-buffer.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    Buffer::Buffer(const VulkanRenderer &renderer, const VkBufferCreateInfo &createInfo,
                   const VkMemoryPropertyFlags memoryProperties, void *data, VkDeviceSize size)
        : Handler("buffer",
                  [&renderer](const VkBuffer &buffer) {
                      vkDestroyBuffer(renderer.getLogicalDevice(), buffer, nullptr);
                  })
        , _renderer(renderer)
        , _deviceMemory(nullptr)
        , _size(size)
    {
        BRASIO_LOG_TRACE("Creating buffer", { "CREATE" });
        BRASIO_VULKAN_CHECK(
            vkCreateBuffer(renderer.getLogicalDevice(), &createInfo, nullptr, &getHandle()),
            "create buffer", { "CREATE" });
        BRASIO_LOG_TRACE("Created buffer", { "CREATE" });
        _deviceMemory =
            std::make_unique<Memory>(renderer, *this, memoryProperties, data, createInfo.size);
    }

    void Buffer::copyInto(const Buffer &other)
    {
        if (other.getSize() < _size)
        {
            BRASIO_LOG_ERROR("Destination buffer is smaller than original buffer, copy will result "
                             "in buffer corruption",
                             { "BUFFER" });
        }
        CommandBuffer commandBuffer(_renderer);

        VkBufferCopy copyRegion{};
        copyRegion.size = _size;
        vkCmdCopyBuffer(commandBuffer.getHandle(), getHandle(), other.getHandle(), 1, &copyRegion);
    }

    void Buffer::copyInto(const ImageAttachment &other)
    {
        CommandBuffer commandBuffer(_renderer);

        VkBufferImageCopy region{};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;

        region.imageSubresource = { .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                    .mipLevel = 0,
                                    .baseArrayLayer = 0,
                                    .layerCount = 1 };
        region.imageOffset = { 0, 0, 0 };
        region.imageExtent = { static_cast<uint32_t>(other.getWidth()),
                               static_cast<uint32_t>(other.getHeight()), 1 };

        vkCmdCopyBufferToImage(commandBuffer.getHandle(), getHandle(), other.getImage(),
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

    VkDeviceSize Buffer::getSize() const
    {
        return _size;
    }
} // namespace brasio::renderer::vulkan
