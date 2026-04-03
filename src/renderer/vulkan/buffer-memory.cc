#include <renderer/vulkan/buffer-memory.hh>

#include <cstring>

namespace brasio::renderer::vulkan
{
    BufferMemory::BufferMemory(const PhysicalDeviceType &physicalDevice,
                               const VkDevice &logicalDevice,
                               const Buffer &buffer,
                               VkMemoryPropertyFlags memoryProperties,
                               void *data, size_t size)
        : Handler("buffer memory",
                  [logicalDevice](const VkDeviceMemory &bufferMemory) {
                      vkFreeMemory(logicalDevice, bufferMemory, nullptr);
                  })
        , _logicalDevice(logicalDevice)
        , _size(size)
    {
        BRASIO_LOG_TRACE(std::cout, "Binding buffer memory", { "CREATE" });
        VkMemoryRequirements memoryRequirements;
        vkGetBufferMemoryRequirements(logicalDevice, buffer.getHandle(),
                                      &memoryRequirements);

        VkMemoryAllocateInfo memoryAllocateInfo{};
        memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memoryAllocateInfo.allocationSize = memoryRequirements.size;
        memoryAllocateInfo.memoryTypeIndex = physicalDevice->findMemoryType(
            memoryRequirements.memoryTypeBits, memoryProperties);

        if (vkAllocateMemory(logicalDevice, &memoryAllocateInfo, nullptr,
                             &getHandle())
            != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL(std::cout, "Could not bind buffer memory",
                                { "CREATE" });
        }
        vkBindBufferMemory(logicalDevice, buffer.getHandle(), getHandle(), 0);
        BRASIO_LOG_TRACE(std::cout, "Bound buffer memory", { "CREATE" });

        if (data != nullptr)
        {
            BRASIO_LOG_TRACE(std::cout, "Transferring buffer memory to device",
                             { "CREATE" });
            map();
            setContent(data);
            BRASIO_LOG_TRACE(std::cout, "Transferred buffer memory to device",
                             { "CREATE" });
        }
    }

    void BufferMemory::map()
    {
        vkMapMemory(_logicalDevice, getHandle(), 0, _size, 0, &_deviceData);
    }

    void BufferMemory::unmap()
    {
        vkUnmapMemory(_logicalDevice, getHandle());
    }

    void BufferMemory::setContent(void *content)
    {
        std::memcpy(_deviceData, content, _size);
    }
} // namespace brasio::renderer::vulkan
